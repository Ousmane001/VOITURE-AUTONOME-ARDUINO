/*
 * VOITURE AUTONOME - Niveau 4
 * Système de contrôle principal pour voiture autonome Arduino
 * 
 * Description: Firmware principal pour la gestion d'une voiture autonome
 * de niveau 4 à échelle réduite utilisant Arduino.
 * 
 * Fonctionnalités:
 * - Détection d'obstacles (ultrasons)
 * - Évitement automatique
 * - Suivi de trajectoire
 * - Arrêt d'urgence
 * - Navigation autonome
 */

// ============ CONFIGURATION DES PINS ============
// Capteurs ultrasoniques (avant)
#define TRIG_FRONT 2
#define ECHO_FRONT 3

// Capteurs ultrasoniques (latéraux)
#define TRIG_LEFT 4
#define ECHO_LEFT 5
#define TRIG_RIGHT 6
#define ECHO_RIGHT 7

// Moteurs (L298N ou similaire)
#define MOTOR_LEFT_FORWARD 8
#define MOTOR_LEFT_BACKWARD 9
#define MOTOR_LEFT_SPEED 10  // PWM

#define MOTOR_RIGHT_FORWARD 11
#define MOTOR_RIGHT_BACKWARD 12
#define MOTOR_RIGHT_SPEED 13  // PWM

// LED indicateurs
#define LED_STATUS 13
#define LED_ALERT A0

// Capteur IR (détection de ligne optionnel)
#define IR_LEFT A1
#define IR_CENTER A2
#define IR_RIGHT A3

// Bouton d'arrêt d'urgence
#define EMERGENCY_STOP A4

// ============ CONSTANTES ============
#define SPEED_NORMAL 150        // Vitesse normale (0-255)
#define SPEED_SLOW 100          // Vitesse réduite
#define SPEED_TURN 120          // Vitesse en virage

#define DISTANCE_SAFE 50        // Distance de sécurité (cm)
#define DISTANCE_CRITICAL 20    // Distance critique (cm)
#define DISTANCE_SIDE 30        // Distance latérale minimale (cm)

#define SCAN_DELAY 50           // Délai entre scans (ms)

// ============ ÉTATS DU SYSTÈME ============
enum State {
  STATE_IDLE,
  STATE_FORWARD,
  STATE_TURNING_LEFT,
  STATE_TURNING_RIGHT,
  STATE_BACKING,
  STATE_EMERGENCY_STOP
};

State currentState = STATE_IDLE;

// ============ VARIABLES GLOBALES ============
long distanceFront = 0;
long distanceLeft = 0;
long distanceRight = 0;
bool emergencyStop = false;

unsigned long lastScanTime = 0;

// ============ SETUP ============
void setup() {
  Serial.begin(9600);
  Serial.println("=== VOITURE AUTONOME - Initialisation ===");
  
  // Configuration des pins capteurs ultrasoniques
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  
  // Configuration des pins moteurs
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);
  
  // Configuration des LEDs
  pinMode(LED_STATUS, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  
  // Configuration capteurs IR
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_CENTER, INPUT);
  pinMode(IR_RIGHT, INPUT);
  
  // Configuration bouton d'arrêt d'urgence
  pinMode(EMERGENCY_STOP, INPUT_PULLUP);
  
  // Arrêt initial des moteurs
  stopMotors();
  
  // Signal de démarrage
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_STATUS, HIGH);
    delay(200);
    digitalWrite(LED_STATUS, LOW);
    delay(200);
  }
  
  Serial.println("Système prêt - Démarrage dans 3 secondes...");
  delay(3000);
  
  currentState = STATE_FORWARD;
  Serial.println("=== MODE AUTONOME ACTIVÉ ===");
}

// ============ BOUCLE PRINCIPALE ============
void loop() {
  // Vérification arrêt d'urgence
  checkEmergencyStop();
  
  if (emergencyStop) {
    handleEmergencyStop();
    return;
  }
  
  // Scan des capteurs
  if (millis() - lastScanTime >= SCAN_DELAY) {
    scanEnvironment();
    lastScanTime = millis();
  }
  
  // Machine à états pour la navigation
  navigateAutonomously();
  
  // LED de statut clignotante
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink >= 500) {
    digitalWrite(LED_STATUS, !digitalRead(LED_STATUS));
    lastBlink = millis();
  }
}

// ============ FONCTIONS DE CAPTEURS ============
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);  // Timeout 30ms
  long distance = duration * 0.034 / 2;
  
  // Filtrage des valeurs aberrantes
  if (distance == 0 || distance > 400) {
    distance = 400;  // Valeur maximale
  }
  
  return distance;
}

void scanEnvironment() {
  distanceFront = measureDistance(TRIG_FRONT, ECHO_FRONT);
  distanceLeft = measureDistance(TRIG_LEFT, ECHO_LEFT);
  distanceRight = measureDistance(TRIG_RIGHT, ECHO_RIGHT);
  
  // Debug
  if (Serial.available() > 0 && Serial.read() == 'd') {
    Serial.print("Front: ");
    Serial.print(distanceFront);
    Serial.print(" cm | Left: ");
    Serial.print(distanceLeft);
    Serial.print(" cm | Right: ");
    Serial.print(distanceRight);
    Serial.println(" cm");
  }
}

// ============ FONCTIONS DE NAVIGATION ============
void navigateAutonomously() {
  // Priorité: détection d'obstacle critique
  if (distanceFront < DISTANCE_CRITICAL) {
    currentState = STATE_BACKING;
    digitalWrite(LED_ALERT, HIGH);
  }
  // Obstacle à distance de sécurité
  else if (distanceFront < DISTANCE_SAFE) {
    // Choisir la direction avec le plus d'espace
    if (distanceLeft > distanceRight && distanceLeft > DISTANCE_SIDE) {
      currentState = STATE_TURNING_LEFT;
    } else if (distanceRight > distanceLeft && distanceRight > DISTANCE_SIDE) {
      currentState = STATE_TURNING_RIGHT;
    } else {
      currentState = STATE_BACKING;
    }
    digitalWrite(LED_ALERT, HIGH);
  }
  // Ajustement de trajectoire préventif
  else if (distanceLeft < DISTANCE_SIDE && distanceRight > DISTANCE_SIDE) {
    currentState = STATE_TURNING_RIGHT;
    digitalWrite(LED_ALERT, LOW);
  }
  else if (distanceRight < DISTANCE_SIDE && distanceLeft > DISTANCE_SIDE) {
    currentState = STATE_TURNING_LEFT;
    digitalWrite(LED_ALERT, LOW);
  }
  // Voie libre
  else {
    currentState = STATE_FORWARD;
    digitalWrite(LED_ALERT, LOW);
  }
  
  // Exécution de l'action selon l'état
  executeState();
}

void executeState() {
  switch(currentState) {
    case STATE_FORWARD:
      moveForward(SPEED_NORMAL);
      break;
      
    case STATE_TURNING_LEFT:
      turnLeft(SPEED_TURN);
      break;
      
    case STATE_TURNING_RIGHT:
      turnRight(SPEED_TURN);
      break;
      
    case STATE_BACKING:
      moveBackward(SPEED_SLOW);
      delay(500);  // Recul pendant 500ms
      // Puis tourner vers la direction la plus dégagée
      if (distanceLeft > distanceRight) {
        turnLeft(SPEED_TURN);
        delay(800);
      } else {
        turnRight(SPEED_TURN);
        delay(800);
      }
      break;
      
    case STATE_EMERGENCY_STOP:
      stopMotors();
      break;
      
    case STATE_IDLE:
    default:
      stopMotors();
      break;
  }
}

// ============ FONCTIONS DE CONTRÔLE MOTEUR ============
void moveForward(int speed) {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_SPEED, speed);
  
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_RIGHT_SPEED, speed);
}

void moveBackward(int speed) {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(MOTOR_LEFT_SPEED, speed);
  
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED, speed);
}

void turnLeft(int speed) {
  // Moteur gauche en arrière, moteur droit en avant
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(MOTOR_LEFT_SPEED, speed / 2);
  
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_RIGHT_SPEED, speed);
}

void turnRight(int speed) {
  // Moteur gauche en avant, moteur droit en arrière
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_SPEED, speed);
  
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED, speed / 2);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_SPEED, 0);
  
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_RIGHT_SPEED, 0);
}

// ============ SÉCURITÉ ============
void checkEmergencyStop() {
  // Bouton d'arrêt d'urgence (actif LOW avec pull-up)
  if (digitalRead(EMERGENCY_STOP) == LOW) {
    emergencyStop = true;
  }
}

void handleEmergencyStop() {
  currentState = STATE_EMERGENCY_STOP;
  stopMotors();
  
  // LED d'alerte clignotante rapide
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink >= 100) {
    digitalWrite(LED_ALERT, !digitalRead(LED_ALERT));
    digitalWrite(LED_STATUS, !digitalRead(LED_STATUS));
    lastBlink = millis();
  }
  
  Serial.println("!!! ARRÊT D'URGENCE ACTIVÉ !!!");
  
  // Pour réinitialiser, débrancher et rebrancher
}
