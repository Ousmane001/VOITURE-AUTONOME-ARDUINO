# Spécifications Techniques - Voiture Autonome Niveau 4

## Vue d'ensemble
Ce document décrit les spécifications techniques du projet de voiture autonome de niveau 4 à échelle réduite basée sur Arduino.

## Niveau d'autonomie
**Niveau 4 (SAE)**: Conduite hautement automatisée
- Navigation autonome complète dans un environnement défini
- Détection et évitement d'obstacles
- Prise de décision automatique
- Arrêt d'urgence automatique

## Architecture du système

### 1. Microcontrôleur
- **Modèle recommandé**: Arduino Uno/Mega 2560
- **Processeur**: ATmega328P (Uno) ou ATmega2560 (Mega)
- **Fréquence**: 16 MHz
- **Mémoire Flash**: 32KB (Uno) / 256KB (Mega)
- **SRAM**: 2KB (Uno) / 8KB (Mega)

### 2. Capteurs

#### Capteurs Ultrasoniques (HC-SR04 ou équivalent)
- **Quantité**: 3 unités minimum
  - 1 capteur frontal
  - 1 capteur latéral gauche
  - 1 capteur latéral droit
- **Portée**: 2-400 cm
- **Angle de détection**: 15°
- **Précision**: ±3mm
- **Tension**: 5V DC
- **Fréquence**: 40 kHz

#### Capteurs Infrarouges (optionnel pour suivi de ligne)
- **Quantité**: 3 unités
- **Type**: Détecteurs IR réflectifs
- **Portée**: 2-30 cm

### 3. Système de propulsion

#### Moteurs
- **Type**: Moteurs DC avec réducteur
- **Quantité**: 2 (configuration différentielle)
- **Tension**: 3-6V DC
- **RPM**: 100-200 RPM (avec réducteur)
- **Couple**: Suffisant pour le châssis (≥ 1 kg.cm)

#### Contrôleur de moteurs
- **Type**: L298N ou équivalent (pont H double)
- **Tension d'entrée**: 5-35V
- **Courant max par canal**: 2A
- **PWM**: Support vitesse variable
- **Contrôle**: Direction et vitesse indépendants

### 4. Alimentation

#### Batterie principale
- **Type**: Li-Ion/Li-Po ou 4x AA
- **Tension**: 7.4V (2S Li-Po) ou 6V (4x AA)
- **Capacité**: ≥ 2000mAh
- **Régulation**: 5V pour Arduino via régulateur intégré

#### Distribution
- Circuit 1: Moteurs (direct batterie)
- Circuit 2: Arduino et capteurs (régulé 5V)
- Protection: Fusible ou disjoncteur recommandé

### 5. Sécurité

#### Arrêt d'urgence
- Bouton physique accessible
- Arrêt immédiat de tous les moteurs
- LED d'indication d'état

#### Indicateurs visuels
- LED de statut système (verte)
- LED d'alerte obstacles (rouge/orange)

## Paramètres de navigation

### Distances de sécurité
- **Distance critique**: 20 cm
- **Distance de sécurité**: 50 cm
- **Distance latérale minimum**: 30 cm

### Vitesses
- **Vitesse normale**: 150/255 PWM (~60%)
- **Vitesse réduite**: 100/255 PWM (~40%)
- **Vitesse virage**: 120/255 PWM (~47%)

### Comportements
1. **Avancer**: Voie libre devant (> 50 cm)
2. **Ralentir et tourner**: Obstacle à 20-50 cm
3. **Reculer et tourner**: Obstacle < 20 cm
4. **Ajuster trajectoire**: Obstacle latéral < 30 cm

## Algorithmes

### Machine à états
```
IDLE → FORWARD → TURNING_LEFT/RIGHT → BACKING → EMERGENCY_STOP
```

### Logique de décision
1. Scan environnement (capteurs ultrasoniques)
2. Évaluation distances
3. Sélection action prioritaire
4. Exécution mouvement
5. Retour étape 1

### Fréquence de scan
- 50 ms entre chaque scan complet
- ~20 Hz de rafraîchissement

## Dimensions du châssis (recommandées)

- **Longueur**: 20-30 cm
- **Largeur**: 15-20 cm
- **Hauteur**: 10-15 cm
- **Empattement**: 15-25 cm
- **Voie**: 12-18 cm
- **Poids total**: < 1 kg

## Interface de communication

### Port série (Serial)
- **Vitesse**: 9600 bauds
- **Usage**: Debug et monitoring
- **Commandes**: 
  - `d`: Affichage distances capteurs

## Performance attendue

### Autonomie
- **Durée**: 30-60 minutes selon batterie
- **Distance**: Variable selon l'environnement

### Réactivité
- **Temps de réaction**: < 100 ms
- **Distance d'arrêt**: 5-10 cm à vitesse normale

## Contraintes environnementales

### Conditions d'utilisation
- **Sol**: Plat et régulier
- **Éclairage**: Normal (capteurs IR)
- **Température**: 15-30°C
- **Humidité**: < 70%

### Obstacles détectables
- Hauteur minimum: 5 cm
- Surface réfléchissante pour ultrasons
- Contraste pour capteurs IR

## Extensions possibles

1. **Capteur de distance laser (LIDAR)**
2. **Module GPS** pour navigation outdoor
3. **Caméra** avec traitement d'image
4. **Module Bluetooth/WiFi** pour contrôle à distance
5. **Gyroscope/Accéléromètre** pour stabilisation
6. **Encodeurs rotatifs** pour odométrie
7. **Capteur de luminosité** pour adaptation
8. **Buzzer** pour signaux sonores

## Conformité et sécurité

- Tensions basses (< 12V)
- Protection contre les courts-circuits
- Arrêt d'urgence obligatoire
- LED indicateurs d'état visible
- Isolation des circuits de puissance
