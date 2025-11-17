# 🚗 VOITURE AUTONOME ARDUINO - Niveau 4

Pilotage d'un projet mécatronique consistant à la conception et la production d'une voiture entièrement autonome de niveau 4 à échelle réduite avec Arduino.

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

## 📋 Description du Projet

Ce projet implémente une voiture autonome de **niveau 4 (SAE)** à échelle réduite utilisant une plateforme Arduino. Le véhicule est capable de:

- ✅ Navigation autonome complète dans un environnement défini
- ✅ Détection d'obstacles avec capteurs ultrasoniques (3 directions)
- ✅ Évitement automatique et prise de décision intelligente
- ✅ Ajustement de trajectoire en temps réel
- ✅ Système d'arrêt d'urgence
- ✅ Indicateurs visuels d'état (LEDs)

## 🎯 Niveau d'Autonomie

**Niveau 4 SAE (Society of Automotive Engineers)**
> *Conduite hautement automatisée* - Le système peut gérer toutes les situations de conduite dans un environnement opérationnel défini, sans intervention humaine.

## 🧩 Composants Principaux

### Électronique
- **Microcontrôleur**: Arduino Uno ou Mega 2560
- **Capteurs**: 3x HC-SR04 (ultrasons) pour détection 360°
- **Moteurs**: 2x DC avec réducteur + Driver L298N
- **Alimentation**: Batterie Li-Po 7.4V ou 4x AA
- **Sécurité**: Bouton d'arrêt d'urgence, LEDs indicateurs

### Logiciel
- **Langage**: C++ (Arduino)
- **Architecture**: Machine à états
- **Algorithme**: Navigation réactive avec évitement d'obstacles
- **Fréquence**: ~20 Hz de rafraîchissement capteurs

## 📁 Structure du Projet

```
VOITURE-AUTONOME-ARDUINO/
├── voiture_autonome/
│   └── voiture_autonome.ino      # Firmware principal
├── docs/
│   ├── SPECIFICATIONS_TECHNIQUES.md
│   ├── LISTE_COMPOSANTS.md       # BOM complète avec prix
│   └── GUIDE_INSTALLATION.md     # Guide détaillé montage
├── schemas/
│   └── SCHEMA_CONNEXIONS.md      # Schémas de câblage détaillés
├── examples/
│   ├── test_capteurs_ultrasons.ino
│   ├── test_moteurs.ino
│   └── calibration_vitesses.ino
└── README.md
```

## 🚀 Installation Rapide

### Prérequis
1. Arduino IDE (version 1.8.x ou 2.x)
2. Câble USB pour Arduino
3. Composants listés dans [docs/LISTE_COMPOSANTS.md](docs/LISTE_COMPOSANTS.md)

### Étapes
```bash
# 1. Cloner le dépôt
git clone https://github.com/Ousmane001/VOITURE-AUTONOME-ARDUINO.git
cd VOITURE-AUTONOME-ARDUINO

# 2. Ouvrir le firmware dans Arduino IDE
# Fichier > Ouvrir > voiture_autonome/voiture_autonome.ino

# 3. Sélectionner la carte et le port
# Outils > Type de carte > Arduino Uno (ou Mega)
# Outils > Port > [Sélectionner votre port COM/tty]

# 4. Téléverser
# Croquis > Téléverser (Ctrl+U)
```

Pour un guide détaillé, consultez [docs/GUIDE_INSTALLATION.md](docs/GUIDE_INSTALLATION.md)

## 🔧 Configuration Matérielle

### Brochage Principal

| Composant | Arduino Pin | Description |
|-----------|-------------|-------------|
| **Capteur US Avant** | D2 (TRIG), D3 (ECHO) | Détection frontale |
| **Capteur US Gauche** | D4 (TRIG), D5 (ECHO) | Détection latérale G |
| **Capteur US Droit** | D6 (TRIG), D7 (ECHO) | Détection latérale D |
| **Moteur Gauche** | D8, D9 (DIR), D10 (PWM) | Contrôle moteur G |
| **Moteur Droit** | D11, D12 (DIR), D13 (PWM) | Contrôle moteur D |
| **LED Statut** | D13 | Indicateur système actif |
| **LED Alerte** | A0 | Indicateur obstacle |
| **Arrêt Urgence** | A4 | Bouton sécurité |

Voir le schéma complet: [schemas/SCHEMA_CONNEXIONS.md](schemas/SCHEMA_CONNEXIONS.md)

## 🎮 Utilisation

### Démarrage
1. Placer la voiture sur une surface plane et dégagée
2. Activer l'interrupteur d'alimentation
3. Attendre 3 secondes (initialisation)
4. La voiture démarre automatiquement

### Indicateurs
- **LED verte clignotante**: Système actif
- **LED rouge fixe**: Obstacle détecté
- **LED rouge clignotante rapide**: Arrêt d'urgence

### Arrêt
- **Normal**: Désactiver l'interrupteur
- **Urgence**: Appuyer sur le bouton rouge

### Mode Debug
Connecter en USB pendant le fonctionnement:
1. Ouvrir le moniteur série (9600 bauds)
2. Envoyer 'd' pour afficher les distances des capteurs

## 🧪 Tests et Calibration

### Tests Unitaires

**Test des capteurs**:
```bash
# Téléverser examples/test_capteurs_ultrasons.ino
# Observer les distances dans le moniteur série
```

**Test des moteurs**:
```bash
# Téléverser examples/test_moteurs.ino
# Vérifier que les 2 moteurs tournent correctement
```

**Calibration**:
```bash
# Téléverser examples/calibration_vitesses.ino
# Ajuster les vitesses pour une trajectoire rectiligne
```

## ⚙️ Paramètres Configurables

Dans `voiture_autonome.ino`, vous pouvez ajuster:

```cpp
// Vitesses (0-255)
#define SPEED_NORMAL 150     // Vitesse croisière
#define SPEED_SLOW 100       // Vitesse réduite
#define SPEED_TURN 120       // Vitesse en virage

// Distances de sécurité (cm)
#define DISTANCE_SAFE 50        // Distance de ralentissement
#define DISTANCE_CRITICAL 20    // Distance d'arrêt
#define DISTANCE_SIDE 30        // Marge latérale
```

## 🧠 Architecture Logicielle

### Machine à États
```
IDLE → FORWARD → TURNING_LEFT/RIGHT → BACKING → EMERGENCY_STOP
                     ↑                    ↓
                     └────────────────────┘
```

### Algorithme Principal
1. **Scan** des capteurs ultrasoniques (3 directions)
2. **Analyse** des distances mesurées
3. **Décision** selon priorités de sécurité
4. **Action** moteurs (avancer/tourner/reculer)
5. **Répéter** à 20 Hz

### Logique de Navigation
- **Voie libre** (> 50cm): Avancer
- **Obstacle proche** (20-50cm): Tourner vers espace dégagé
- **Obstacle critique** (< 20cm): Reculer puis tourner
- **Obstacle latéral**: Ajustement préventif de trajectoire

## 💰 Budget

### Configuration Minimale
- **Coût total**: 100-150€
- Fonctionnalités de base opérationnelles

### Configuration Complète
- **Coût total**: 130-210€
- Capteurs additionnels et extensions

Détails dans [docs/LISTE_COMPOSANTS.md](docs/LISTE_COMPOSANTS.md)

## 📚 Documentation

| Document | Description |
|----------|-------------|
| [SPECIFICATIONS_TECHNIQUES.md](docs/SPECIFICATIONS_TECHNIQUES.md) | Spécifications complètes du système |
| [LISTE_COMPOSANTS.md](docs/LISTE_COMPOSANTS.md) | BOM avec références et prix |
| [GUIDE_INSTALLATION.md](docs/GUIDE_INSTALLATION.md) | Guide de montage détaillé |
| [SCHEMA_CONNEXIONS.md](schemas/SCHEMA_CONNEXIONS.md) | Schémas de câblage complets |

## 🔒 Sécurité

- ⚠️ **Toujours utiliser des batteries appropriées** (protection court-circuit)
- ⚠️ **Vérifier toutes les connexions** avant mise sous tension
- ⚠️ **Bouton d'arrêt d'urgence obligatoire** et facilement accessible
- ⚠️ **Tester dans un espace sécurisé** sans obstacles fragiles
- ⚠️ **Surveiller la température** du driver moteur (L298N peut chauffer)

## 🛠️ Dépannage

| Problème | Solution |
|----------|----------|
| Rien ne s'allume | Vérifier batterie et interrupteur |
| Moteurs ne tournent pas | Vérifier connexions L298N et jumpers ENA/ENB |
| Capteurs ne répondent pas | Vérifier câblage TRIG/ECHO et alimentation 5V |
| Voiture tourne en cercle | Calibrer les vitesses (voir examples/) |
| Comportement erratique | Recharger batterie, vérifier GND communs |

## 📈 Évolutions Possibles

### Phase 1 (Court terme)
- [ ] Ajout d'un servo pour scan panoramique
- [ ] Module Bluetooth pour contrôle à distance
- [ ] Capteurs IR pour suivi de ligne

### Phase 2 (Moyen terme)
- [ ] Caméra avec traitement d'image
- [ ] Gyroscope/Accéléromètre pour stabilisation
- [ ] Encodeurs rotatifs pour odométrie

### Phase 3 (Long terme)
- [ ] GPS pour navigation outdoor
- [ ] LIDAR pour cartographie
- [ ] Intelligence artificielle (apprentissage)

## 🤝 Contribution

Les contributions sont les bienvenues! Pour contribuer:

1. Fork le projet
2. Créer une branche (`git checkout -b feature/amelioration`)
3. Commit les changements (`git commit -m 'Ajout fonctionnalité'`)
4. Push vers la branche (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request

## 📝 Licence

Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.

## 👥 Auteurs

- **Ousmane001** - *Créateur du projet*

## 🙏 Remerciements

- Communauté Arduino pour les bibliothèques et ressources
- Tutoriels HowToMechatronics pour les guides capteurs
- Makers et passionnés de robotique

## 📧 Contact

Pour questions ou support:
- **GitHub Issues**: [Ouvrir un ticket](https://github.com/Ousmane001/VOITURE-AUTONOME-ARDUINO/issues)
- **Forum Arduino**: [arduino.cc/forum](https://forum.arduino.cc/)

## 🌟 Support

Si ce projet vous a été utile, n'hésitez pas à lui donner une ⭐ sur GitHub!

---

**Note**: Ce projet est à but éducatif. Toujours suivre les consignes de sécurité lors de la manipulation de composants électroniques.

*Fait avec ❤️ et Arduino*
