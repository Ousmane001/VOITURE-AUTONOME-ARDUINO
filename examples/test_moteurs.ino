/*
 * Test des Moteurs avec Driver L298N
 * 
 * Ce programme teste les moteurs et le driver L298N
 * en exécutant une séquence de mouvements de base.
 * 
 * Utilisation:
 * 1. Téléverser ce code sur l'Arduino
 * 2. Placer la voiture sur une surface dégagée
 * 3. Observer les mouvements
 * 4. Vérifier que les deux moteurs tournent correctement
 */

// Configuration des pins moteurs
#define MOTOR_LEFT_FORWARD 8
#define MOTOR_LEFT_BACKWARD 9
#define MOTOR_LEFT_SPEED 10

#define MOTOR_RIGHT_FORWARD 11
#define MOTOR_RIGHT_BACKWARD 12
#define MOTOR_RIGHT_SPEED 13

// Vitesse de test
#define TEST_SPEED 150

void setup() {
  Serial.begin(9600);
  Serial.println("=== Test Moteurs ===");
  
  // Configuration des pins
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);
  
  // Arrêt initial
  stopMotors();
  
  Serial.println("Démarrage du test dans 3 secondes...");
  delay(3000);
}

void loop() {
  Serial.println("Test 1: Avancer");
  moveForward(TEST_SPEED);
  delay(2000);
  
  stopMotors();
  delay(1000);
  
  Serial.println("Test 2: Reculer");
  moveBackward(TEST_SPEED);
  delay(2000);
  
  stopMotors();
  delay(1000);
  
  Serial.println("Test 3: Tourner à gauche");
  turnLeft(TEST_SPEED);
  delay(1500);
  
  stopMotors();
  delay(1000);
  
  Serial.println("Test 4: Tourner à droite");
  turnRight(TEST_SPEED);
  delay(1500);
  
  stopMotors();
  delay(1000);
  
  Serial.println("Test 5: Moteur gauche seul");
  testLeftMotor();
  delay(1000);
  
  Serial.println("Test 6: Moteur droit seul");
  testRightMotor();
  delay(1000);
  
  Serial.println("\n=== Cycle de test terminé ===");
  Serial.println("Pause 5 secondes...\n");
  delay(5000);
}

// Fonctions de mouvement
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
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(MOTOR_LEFT_SPEED, speed / 2);
  
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_RIGHT_SPEED, speed);
}

void turnRight(int speed) {
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

void testLeftMotor() {
  Serial.println("  - Avant");
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_SPEED, TEST_SPEED);
  delay(1500);
  
  Serial.println("  - Arrêt");
  stopMotors();
  delay(500);
  
  Serial.println("  - Arrière");
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(MOTOR_LEFT_SPEED, TEST_SPEED);
  delay(1500);
  
  stopMotors();
}

void testRightMotor() {
  Serial.println("  - Avant");
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_RIGHT_SPEED, TEST_SPEED);
  delay(1500);
  
  Serial.println("  - Arrêt");
  stopMotors();
  delay(500);
  
  Serial.println("  - Arrière");
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED, TEST_SPEED);
  delay(1500);
  
  stopMotors();
}
