/*
 * Calibration des Vitesses
 * 
 * Ce programme aide à calibrer les vitesses des moteurs
 * pour obtenir un déplacement rectiligne.
 * 
 * Utilisation:
 * 1. Téléverser ce code sur l'Arduino
 * 2. Ouvrir le moniteur série (9600 bauds)
 * 3. Envoyer des commandes pour ajuster les vitesses:
 *    - '+' : Augmenter vitesse moteur gauche
 *    - '-' : Diminuer vitesse moteur gauche
 *    - '*' : Augmenter vitesse moteur droit
 *    - '/' : Diminuer vitesse moteur droit
 *    - 's' : Afficher les vitesses actuelles
 *    - 't' : Tester le mouvement avant (3 secondes)
 *    - 'r' : Réinitialiser aux valeurs par défaut
 */

// Configuration des pins moteurs
#define MOTOR_LEFT_FORWARD 8
#define MOTOR_LEFT_BACKWARD 9
#define MOTOR_LEFT_SPEED 10

#define MOTOR_RIGHT_FORWARD 11
#define MOTOR_RIGHT_BACKWARD 12
#define MOTOR_RIGHT_SPEED 13

// Vitesses initiales
int speedLeft = 150;
int speedRight = 150;
const int speedIncrement = 5;

void setup() {
  Serial.begin(9600);
  Serial.println("=== Calibration des Vitesses ===");
  Serial.println();
  
  // Configuration des pins
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);
  
  // Arrêt initial
  stopMotors();
  
  printHelp();
  printSpeeds();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    switch(command) {
      case '+':
        speedLeft += speedIncrement;
        if (speedLeft > 255) speedLeft = 255;
        Serial.println("Vitesse gauche augmentée");
        printSpeeds();
        break;
        
      case '-':
        speedLeft -= speedIncrement;
        if (speedLeft < 0) speedLeft = 0;
        Serial.println("Vitesse gauche diminuée");
        printSpeeds();
        break;
        
      case '*':
        speedRight += speedIncrement;
        if (speedRight > 255) speedRight = 255;
        Serial.println("Vitesse droite augmentée");
        printSpeeds();
        break;
        
      case '/':
        speedRight -= speedIncrement;
        if (speedRight < 0) speedRight = 0;
        Serial.println("Vitesse droite diminuée");
        printSpeeds();
        break;
        
      case 's':
        printSpeeds();
        break;
        
      case 't':
        testMovement();
        break;
        
      case 'r':
        speedLeft = 150;
        speedRight = 150;
        Serial.println("Vitesses réinitialisées");
        printSpeeds();
        break;
        
      case 'h':
        printHelp();
        break;
        
      default:
        // Ignorer les caractères non reconnus
        break;
    }
  }
}

void printHelp() {
  Serial.println("Commandes disponibles:");
  Serial.println("  '+' : Augmenter vitesse moteur gauche");
  Serial.println("  '-' : Diminuer vitesse moteur gauche");
  Serial.println("  '*' : Augmenter vitesse moteur droit");
  Serial.println("  '/' : Diminuer vitesse moteur droit");
  Serial.println("  's' : Afficher les vitesses");
  Serial.println("  't' : Tester le mouvement (3s)");
  Serial.println("  'r' : Réinitialiser (150/150)");
  Serial.println("  'h' : Afficher cette aide");
  Serial.println();
}

void printSpeeds() {
  Serial.print("Vitesses actuelles - Gauche: ");
  Serial.print(speedLeft);
  Serial.print(" / Droite: ");
  Serial.println(speedRight);
  
  // Calculer et afficher le ratio
  if (speedRight > 0) {
    float ratio = (float)speedLeft / (float)speedRight;
    Serial.print("Ratio G/D: ");
    Serial.println(ratio, 3);
  }
  
  // Afficher le code à copier
  Serial.println("\nCode à utiliser:");
  Serial.print("  speedLeft = ");
  Serial.print(speedLeft);
  Serial.println(";");
  Serial.print("  speedRight = ");
  Serial.print(speedRight);
  Serial.println(";");
  Serial.println();
}

void testMovement() {
  Serial.println("=== Test de mouvement (3 secondes) ===");
  Serial.println("Observez si la voiture va droit...");
  Serial.println();
  
  moveForward();
  delay(3000);
  stopMotors();
  
  Serial.println("Test terminé. Ajustez si nécessaire.");
  Serial.println("Si la voiture va:");
  Serial.println("  - Vers la GAUCHE : augmenter vitesse GAUCHE (+)");
  Serial.println("  - Vers la DROITE : augmenter vitesse DROITE (*)");
  Serial.println();
}

void moveForward() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_SPEED, speedLeft);
  
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_RIGHT_SPEED, speedRight);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_SPEED, 0);
  
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_RIGHT_SPEED, 0);
}
