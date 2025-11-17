# Guide d'Installation et de Montage

## Prérequis

### Logiciels
1. **Arduino IDE** (version 1.8.x ou 2.x)
   - Télécharger: https://www.arduino.cc/en/software
   - Installation standard pour votre OS

2. **Drivers USB** (si nécessaire)
   - Windows: CH340/CH341 drivers pour clones Arduino
   - macOS/Linux: Généralement inclus

### Connaissances Requises
- Bases d'électronique (Loi d'Ohm)
- Soudure simple (optionnel mais recommandé)
- Programmation Arduino de base
- Utilisation multimètre

## Étape 1: Préparation du Matériel

### Inventaire
1. Vérifier tous les composants selon la liste BOM
2. Tester les composants individuellement:
   - Arduino: connexion USB et LED power
   - Moteurs: fonctionnement à batterie directe
   - Capteurs: avec code de test simple

### Organisation
1. Préparer un espace de travail propre
2. Outils à portée de main
3. Bonne lumière
4. Surface anti-statique recommandée

## Étape 2: Installation de l'Arduino IDE

### Windows
```
1. Télécharger l'installeur depuis arduino.cc
2. Exécuter le fichier .exe
3. Suivre l'assistant d'installation
4. Accepter l'installation des drivers USB
```

### macOS
```
1. Télécharger le fichier .dmg
2. Glisser Arduino dans Applications
3. Ouvrir depuis Applications
4. Accepter l'ouverture (Préférences Système > Sécurité)
```

### Linux (Ubuntu/Debian)
```bash
# Méthode 1: Snap (recommandé)
sudo snap install arduino

# Méthode 2: Téléchargement manuel
wget https://downloads.arduino.cc/arduino-X.X.X-linux64.tar.xz
tar -xf arduino-X.X.X-linux64.tar.xz
cd arduino-X.X.X
sudo ./install.sh

# Ajouter l'utilisateur au groupe dialout
sudo usermod -a -G dialout $USER
# Redémarrer la session
```

### Configuration IDE
1. Ouvrir Arduino IDE
2. **Fichier > Préférences**
   - Activer "Affichage des numéros de ligne"
   - Augmenter la taille de police si nécessaire
3. **Outils > Type de carte**: Sélectionner "Arduino Uno" ou "Arduino Mega"
4. **Outils > Port**: Sélectionner le port COM/tty correct

## Étape 3: Téléchargement du Code

### Option A: Git (recommandé)
```bash
git clone https://github.com/Ousmane001/VOITURE-AUTONOME-ARDUINO.git
cd VOITURE-AUTONOME-ARDUINO
```

### Option B: ZIP
1. Télécharger depuis GitHub (bouton "Code" > "Download ZIP")
2. Extraire dans un dossier de travail
3. Ouvrir le dossier

## Étape 4: Montage du Châssis

### Châssis Commercial
1. Suivre les instructions du fabricant
2. Assembler les supports moteurs
3. Fixer les roues
4. Installer les roulettes folles (casters)

### Châssis DIY (Acrylique)
1. Découper la plaque (20x15cm recommandé)
2. Percer les trous de fixation:
   - Moteurs: 4 trous par moteur (M3)
   - Arduino: 4 trous selon entraxe
   - Breadboard: surface adhésive
3. Limer les bords
4. Nettoyer la plaque

### Installation des Moteurs
1. Fixer les supports moteurs au châssis (vis M3)
2. Vérifier l'alignement parallèle
3. Installer les roues sur les axes
4. Tester la rotation libre
5. Fixer les roulettes à l'opposé

## Étape 5: Câblage Électronique

### Schéma de Principe

```
[Batterie] ─┬─> [Driver L298N VCC]
            │
            ├─> [Arduino Vin/5V via régulateur]
            │
            └─> [Interrupteur général]

[L298N] ─┬─> Moteur Gauche
         └─> Moteur Droit

[Arduino] ─┬─> Capteurs (5V, GND, Signal)
           ├─> L298N (Pins contrôle)
           └─> LED et boutons
```

### Connexions Détaillées

#### Alimentation
```
Batterie (+) ──> Interrupteur ──> L298N (12V)
Batterie (-)  ────────────────> L298N (GND)
L298N (5V out) ───────────────> Arduino (5V)
L298N (GND) ──────────────────> Arduino (GND)
```

#### Driver Moteur L298N
```
Arduino → L298N
  Pin 8  → IN1 (Moteur G avant)
  Pin 9  → IN2 (Moteur G arrière)
  Pin 10 → ENA (PWM Moteur G)
  Pin 11 → IN3 (Moteur D avant)
  Pin 12 → IN4 (Moteur D arrière)
  Pin 13 → ENB (PWM Moteur D)
  GND    → GND

L298N → Moteurs
  OUT1, OUT2 → Moteur Gauche
  OUT3, OUT4 → Moteur Droit
```

**Note**: Jumpers ENA/ENB retirés pour contrôle PWM

#### Capteurs Ultrasoniques
```
Arduino → HC-SR04 (Avant)
  Pin 2  → TRIG
  Pin 3  → ECHO
  5V     → VCC
  GND    → GND

Arduino → HC-SR04 (Gauche)
  Pin 4  → TRIG
  Pin 5  → ECHO
  5V     → VCC
  GND    → GND

Arduino → HC-SR04 (Droite)
  Pin 6  → TRIG
  Pin 7  → ECHO
  5V     → VCC
  GND    → GND
```

#### LED et Boutons
```
Arduino → LED Statut (Verte)
  Pin 13 → Résistance 220Ω → LED (+) → GND

Arduino → LED Alerte (Rouge)
  Pin A0 → Résistance 220Ω → LED (+) → GND

Arduino → Bouton Arrêt Urgence
  Pin A4 → Bouton → GND
  (Pull-up interne activé)
```

#### Capteurs IR (Optionnels)
```
Arduino → Capteurs IR
  Pin A1 → IR Gauche (OUT)
  Pin A2 → IR Centre (OUT)
  Pin A3 → IR Droite (OUT)
  5V     → VCC (tous)
  GND    → GND (tous)
```

### Conseils de Câblage

1. **Utiliser des couleurs**:
   - Rouge: Alimentation positive
   - Noir: Masse (GND)
   - Autres couleurs: Signaux

2. **Organiser les câbles**:
   - Serre-câbles pour regrouper
   - Longueur appropriée (pas trop long)
   - Éviter les croisements

3. **Sécurité**:
   - Vérifier TOUTES les connexions avant mise sous tension
   - Pas de courts-circuits
   - Polarités correctes
   - Soudures solides si utilisées

4. **Tests progressifs**:
   - Tester chaque sous-système séparément
   - Ajouter les composants un par un
   - Vérifier au multimètre

## Étape 6: Fixation des Composants

### Répartition des Masses
```
Vue de dessus du châssis:

  [Avant]
  ┌─────────────────┐
  │   [Capteur F]   │
  │                 │
  │ [C]         [C] │  C = Capteurs latéraux
  │  G           D  │
  │                 │
  │   [Arduino]     │
  │   [L298N]       │
  │                 │
  │   [Batterie]    │
  │                 │
  │ [M]         [M] │  M = Moteurs
  └─────────────────┘
  [Arrière - Roulettes]
```

### Fixations Recommandées

1. **Arduino**:
   - Vis M3 sur entretoises (10-15mm)
   - Ou mousse double-face
   - Accès facile au port USB

2. **L298N**:
   - Vis M3 sur entretoises
   - Dissipateur thermique visible
   - Accès aux borniers

3. **Breadboard**:
   - Surface adhésive incluse
   - Position centrale
   - Câbles courts vers Arduino

4. **Batterie**:
   - Velcro adhésif (retrait facile)
   - Position basse (centre de gravité)
   - Interrupteur accessible

5. **Capteurs**:
   - Supports fixes ou servo mobile
   - Hauteur: 5-10cm du sol
   - Orientation: légèrement vers le haut (5°)
   - Espacement libre autour (pas d'obstruction)

## Étape 7: Configuration et Upload du Code

### Ouverture du Projet
1. Ouvrir Arduino IDE
2. **Fichier > Ouvrir**
3. Naviguer vers `voiture_autonome/voiture_autonome.ino`
4. Le code s'ouvre avec les onglets nécessaires

### Vérification du Code
1. **Outils > Type de carte**: Arduino Uno/Mega
2. **Outils > Port**: Sélectionner le bon port COM
3. **Croquis > Vérifier/Compiler** (Ctrl+R)
4. Attendre la compilation (aucune erreur attendue)

### Configuration Personnalisée (Si Nécessaire)

Éditer les constantes dans le code si besoin:

```cpp
// Ajuster les vitesses selon vos moteurs
#define SPEED_NORMAL 150   // Augmenter si trop lent
#define SPEED_SLOW 100
#define SPEED_TURN 120

// Ajuster les distances selon votre environnement
#define DISTANCE_SAFE 50        // Distance sécurité (cm)
#define DISTANCE_CRITICAL 20    // Distance critique (cm)
```

### Upload vers l'Arduino
1. Connecter l'Arduino via USB
2. **Croquis > Téléverser** (Ctrl+U)
3. Attendre l'upload (LEDs RX/TX clignotent)
4. Message "Téléversement terminé" attendu

### Vérification du Fonctionnement

**Sans moteurs alimentés**:
1. Ouvrir **Outils > Moniteur série**
2. Régler sur **9600 bauds**
3. Observer les messages d'initialisation
4. LED de statut doit clignoter
5. Approcher la main des capteurs
6. LED d'alerte doit s'allumer si obstacle détecté

## Étape 8: Tests et Calibration

### Test 1: Capteurs Seuls
```
1. Alimenter uniquement l'Arduino (USB)
2. Ouvrir le moniteur série
3. Envoyer 'd' pour debug
4. Observer les distances affichées
5. Approcher/éloigner obstacles
6. Vérifier cohérence des valeurs
```

### Test 2: Moteurs Seuls
```
1. Déconnecter les capteurs
2. Alimenter le système complet
3. Les moteurs doivent tourner
4. Vérifier le sens de rotation
5. Si inversé: échanger fils moteur
```

### Test 3: Système Complet
```
1. Tout reconnecter
2. Placer sur une surface dégagée
3. Alimenter le système
4. Attendre les 3 bips LED
5. Observer le comportement autonome
6. Tester l'arrêt d'urgence
```

### Calibration

#### Si la voiture tourne en cercle:
- Vérifier l'alignement des roues
- Ajuster les vitesses relatives des moteurs dans le code
- Vérifier que les roues sont identiques

#### Si les capteurs réagissent mal:
- Vérifier les connexions
- Nettoyer les capteurs
- Ajuster les seuils de distance
- Vérifier l'angle de montage

#### Si la vitesse est incorrecte:
- Ajuster les valeurs PWM (SPEED_NORMAL, etc.)
- Vérifier la charge de la batterie
- Vérifier le couple des moteurs

## Étape 9: Utilisation

### Démarrage
1. S'assurer que la zone est dégagée
2. Placer la voiture au sol
3. Activer l'interrupteur principal
4. Attendre 3 secondes (initialisation)
5. La voiture démarre automatiquement

### Surveillance
- Observer les LED indicateurs
- LED verte: Système actif
- LED rouge: Obstacle détecté
- Clignotement rapide: Arrêt d'urgence

### Arrêt
- **Normal**: Désactiver l'interrupteur
- **Urgence**: Appuyer sur le bouton rouge

### Debug
- Connecter en USB pendant fonctionnement
- Ouvrir le moniteur série (9600 bauds)
- Envoyer 'd' pour voir les distances

## Dépannage

### Problème: Rien ne s'allume
- Vérifier la batterie (charge suffisante)
- Vérifier l'interrupteur
- Vérifier les connexions d'alimentation
- Mesurer tension au multimètre

### Problème: Arduino fonctionne mais pas les moteurs
- Vérifier l'alimentation du L298N
- Vérifier les connexions IN1-IN4, ENA, ENB
- Vérifier les jumpers ENA/ENB retirés
- Tester moteurs directement sur batterie

### Problème: Capteurs ne répondent pas
- Vérifier connexions TRIG/ECHO
- Vérifier alimentation 5V capteurs
- Tester capteurs avec code simple
- Nettoyer les transducteurs

### Problème: Comportement erratique
- Recharger la batterie
- Vérifier tous les GND communs
- Vérifier absence de courts-circuits
- Re-téléverser le code

### Problème: Compilation échoue
- Vérifier sélection de la bonne carte
- Fermer/réouvrir Arduino IDE
- Vérifier syntaxe du code (pas de modifications)
- Réinstaller Arduino IDE si nécessaire

## Améliorations Futures

1. **Ajout d'un servo** pour scan panoramique
2. **Module Bluetooth** pour contrôle mobile
3. **Caméra** pour vision artificielle
4. **Encodeurs** pour odométrie précise
5. **Buzzer** pour feedback sonore
6. **Écran LCD** pour affichage d'informations

## Ressources Supplémentaires

- [Documentation Arduino](https://www.arduino.cc/reference/)
- [Tutoriel HC-SR04](https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/)
- [L298N Guide](https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/)
- Forum Arduino FR: [arduino.cc/forum](https://forum.arduino.cc/)

## Support

Pour questions ou problèmes:
1. Consulter la documentation
2. Vérifier les issues GitHub du projet
3. Poster dans le forum Arduino
4. Contacter le créateur du projet

Bon montage et bonne route autonome ! 🚗🤖
