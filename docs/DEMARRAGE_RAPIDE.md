# 🚀 Guide de Démarrage Rapide

Ce guide vous permet de démarrer rapidement avec votre voiture autonome Arduino.

## ⚡ En 5 Minutes

### 1. Matériel Requis (Minimum)
- Arduino Uno
- 1 capteur HC-SR04 (avant)
- 2 moteurs DC + L298N
- Batterie 7.4V
- Châssis avec roues
- Quelques câbles Dupont

### 2. Connexions Essentielles
```
CAPTEUR AVANT:
  Arduino D2 → HC-SR04 TRIG
  Arduino D3 → HC-SR04 ECHO
  Arduino 5V → HC-SR04 VCC
  Arduino GND → HC-SR04 GND

MOTEURS (via L298N):
  Arduino D8, D9, D10 → L298N (moteur gauche)
  Arduino D11, D12, D13 → L298N (moteur droit)

BATTERIE:
  Batterie → L298N VCC
  L298N 5V → Arduino 5V
```

### 3. Code
1. Télécharger: [voiture_autonome.ino](../voiture_autonome/voiture_autonome.ino)
2. Ouvrir dans Arduino IDE
3. Sélectionner: **Outils > Type de carte > Arduino Uno**
4. Sélectionner: **Outils > Port > [Votre port]**
5. Cliquer: **Téléverser** (flèche →)

### 4. Test
1. Placer la voiture au sol
2. Allumer l'alimentation
3. La LED clignote 3 fois
4. La voiture démarre après 3 secondes

## 🎯 Configuration de Base vs Complète

### Configuration Minimale (1 capteur)
✅ Détection frontale uniquement
✅ Évitement d'obstacles basique
❌ Pas de détection latérale
⚠️ Peut rester bloqué dans certaines situations

**Code modifié**:
```cpp
// Dans navigateAutonomously(), simplifier:
void navigateAutonomously() {
  if (distanceFront < DISTANCE_CRITICAL) {
    // Reculer
    moveBackward(SPEED_SLOW);
    delay(500);
    // Tourner aléatoirement
    if (random(2) == 0) {
      turnLeft(SPEED_TURN);
    } else {
      turnRight(SPEED_TURN);
    }
    delay(800);
  }
  else if (distanceFront < DISTANCE_SAFE) {
    // Tourner
    turnRight(SPEED_TURN);
  }
  else {
    // Avancer
    moveForward(SPEED_NORMAL);
  }
}
```

### Configuration Complète (3 capteurs)
✅ Détection 360° (avant + latéraux)
✅ Évitement intelligent
✅ Choix optimal de direction
✅ Navigation robuste

**Utiliser le code original** sans modification.

## 🔧 Premiers Tests

### Test 1: LEDs (Sans moteurs)
```cpp
// Dans setup(), ajouter après les pinMode():
void setup() {
  // ... autres setup ...
  
  // Test LEDs
  digitalWrite(LED_STATUS, HIGH);
  delay(1000);
  digitalWrite(LED_STATUS, LOW);
  
  digitalWrite(LED_ALERT, HIGH);
  delay(1000);
  digitalWrite(LED_ALERT, LOW);
}
```

### Test 2: Capteur Seul
Utiliser: [examples/test_capteurs_ultrasons.ino](../examples/test_capteurs_ultrasons.ino)
- Ouvrir moniteur série (9600 bauds)
- Observer les distances
- Vérifier réactivité aux obstacles

### Test 3: Moteurs Seuls
Utiliser: [examples/test_moteurs.ino](../examples/test_moteurs.ino)
- Placer sur cales (roues en l'air)
- Observer rotation des moteurs
- Vérifier direction correcte

### Test 4: Système Complet
1. Assembler complètement
2. Téléverser voiture_autonome.ino
3. Placer sur surface dégagée
4. Allumer et observer

## ⚙️ Ajustements Rapides

### La voiture tourne en cercle
**Cause**: Moteurs déséquilibrés
**Solution**:
```cpp
// Dans le code, ajuster les vitesses:
void moveForward(int speed) {
  analogWrite(MOTOR_LEFT_SPEED, speed);
  analogWrite(MOTOR_RIGHT_SPEED, speed * 0.95); // Ajuster ce facteur
}
```

### Obstacle non détecté
**Cause**: Capteur mal orienté ou défectueux
**Solution**:
1. Vérifier l'angle du capteur (légèrement vers le haut)
2. Nettoyer les transducteurs
3. Tester avec examples/test_capteurs_ultrasons.ino

### Moteurs ne démarrent pas
**Cause**: Alimentation insuffisante
**Solution**:
1. Vérifier charge batterie (> 6V)
2. Vérifier jumpers ENA/ENB retirés sur L298N
3. Mesurer tension aux bornes moteurs

### Comportement erratique
**Cause**: Batterie faible ou GND non communs
**Solution**:
1. Recharger/remplacer batterie
2. Vérifier que tous les GND sont reliés
3. Ajouter condensateur 100µF sur batterie

## 📊 Paramètres à Modifier Selon Votre Setup

### Vitesses (Trop lent/rapide)
```cpp
#define SPEED_NORMAL 150    // Augmenter: 150→180
#define SPEED_SLOW 100      // Ajuster proportionnellement
#define SPEED_TURN 120      // Ajuster proportionnellement
```

### Distances (Environnement petit/grand)
```cpp
// Environnement petit (< 2m²)
#define DISTANCE_SAFE 30        // Au lieu de 50
#define DISTANCE_CRITICAL 15    // Au lieu de 20

// Environnement grand (> 4m²)
#define DISTANCE_SAFE 70        // Au lieu de 50
#define DISTANCE_CRITICAL 30    // Au lieu de 20
```

### Réactivité (Lent/Nerveux)
```cpp
#define SCAN_DELAY 50       // Plus petit = plus réactif
                           // Plus grand = plus stable
// Essayer: 30ms (rapide) ou 100ms (lent)
```

## 🐛 Dépannage Express

| Symptôme | Solution Rapide |
|----------|----------------|
| Rien ne marche | Vérifier interrupteur + batterie chargée |
| Moteurs silencieux | Retirer jumpers ENA/ENB sur L298N |
| LED ne s'allument pas | Vérifier résistances 220Ω |
| Tourne en rond | Utiliser calibration_vitesses.ino |
| Ne s'arrête pas devant obstacle | Nettoyer capteur + vérifier orientation |
| Redémarre en boucle | Batterie trop faible, charger/remplacer |

## 📖 Pour Aller Plus Loin

Une fois le système de base fonctionnel:

1. **Ajouter capteurs latéraux** (voir schéma complet)
2. **Optimiser la navigation** (ajuster paramètres)
3. **Ajouter Bluetooth** (contrôle smartphone)
4. **Implémenter suivi de ligne** (capteurs IR)
5. **Ajouter servo scan** (vision panoramique)

## 📞 Aide

Problème non résolu? Consultez:
- [Guide Installation Complet](GUIDE_INSTALLATION.md)
- [Schémas Connexions](../schemas/SCHEMA_CONNEXIONS.md)
- [Spécifications Techniques](SPECIFICATIONS_TECHNIQUES.md)
- [GitHub Issues](https://github.com/Ousmane001/VOITURE-AUTONOME-ARDUINO/issues)

## ✅ Checklist de Démarrage

Avant le premier démarrage, vérifier:

- [ ] Batterie chargée (> 7V pour Li-Po, > 5.5V pour AA)
- [ ] Tous les GND connectés ensemble
- [ ] Pas de court-circuit (vérifier au multimètre)
- [ ] Jumpers ENA/ENB retirés sur L298N
- [ ] Capteurs orientés correctement
- [ ] Roues libres de tourner
- [ ] Espace de test dégagé (2x2m minimum)
- [ ] Bouton d'arrêt d'urgence accessible
- [ ] Code compilé et téléversé sans erreur

**Tout est OK?** → Allumez et profitez! 🎉

## 🎬 Première Utilisation

1. ⚡ Allumer l'interrupteur
2. 💡 Observer 3 clignotements de la LED
3. ⏱️ Attendre 3 secondes (compte à rebours interne)
4. 🚗 La voiture démarre automatiquement
5. 👀 Observer le comportement:
   - LED verte clignote = système actif
   - LED rouge s'allume = obstacle détecté
   - Voiture tourne/recule = évitement en cours
6. 🛑 En cas de problème: bouton d'arrêt d'urgence

**Bon démarrage!** 🏁
