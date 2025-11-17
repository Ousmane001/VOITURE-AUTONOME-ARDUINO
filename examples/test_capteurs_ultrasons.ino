/*
 * Test des Capteurs Ultrasoniques HC-SR04
 * 
 * Ce programme teste les 3 capteurs ultrasoniques
 * et affiche les distances mesurées sur le moniteur série.
 * 
 * Utilisation:
 * 1. Téléverser ce code sur l'Arduino
 * 2. Ouvrir le moniteur série (9600 bauds)
 * 3. Observer les distances mesurées
 * 4. Approcher/éloigner des obstacles pour tester
 */

// Configuration des pins
#define TRIG_FRONT 2
#define ECHO_FRONT 3
#define TRIG_LEFT 4
#define ECHO_LEFT 5
#define TRIG_RIGHT 6
#define ECHO_RIGHT 7

void setup() {
  Serial.begin(9600);
  Serial.println("=== Test Capteurs Ultrasoniques ===");
  Serial.println("Initialisation...");
  
  // Configuration des pins
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  
  Serial.println("Capteurs prêts!");
  Serial.println("Format: Avant | Gauche | Droite (en cm)");
  Serial.println("----------------------------------------");
  delay(1000);
}

void loop() {
  // Mesurer les distances
  long distanceFront = measureDistance(TRIG_FRONT, ECHO_FRONT);
  long distanceLeft = measureDistance(TRIG_LEFT, ECHO_LEFT);
  long distanceRight = measureDistance(TRIG_RIGHT, ECHO_RIGHT);
  
  // Afficher les résultats
  Serial.print("Avant: ");
  Serial.print(distanceFront);
  Serial.print(" cm | Gauche: ");
  Serial.print(distanceLeft);
  Serial.print(" cm | Droite: ");
  Serial.print(distanceRight);
  Serial.println(" cm");
  
  // Alerte si obstacle proche
  if (distanceFront < 20 || distanceLeft < 20 || distanceRight < 20) {
    Serial.println("!!! OBSTACLE PROCHE !!!");
  }
  
  delay(500); // Pause entre mesures
}

long measureDistance(int trigPin, int echoPin) {
  // Pulse TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Mesurer le temps d'écho
  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout 30ms
  
  // Calculer la distance (vitesse son = 340m/s)
  long distance = duration * 0.034 / 2;
  
  // Filtrage des valeurs aberrantes
  if (distance == 0 || distance > 400) {
    distance = 400; // Hors de portée
  }
  
  return distance;
}
