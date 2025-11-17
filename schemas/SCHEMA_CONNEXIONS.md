# Schéma de Connexions - Voiture Autonome

## Vue d'ensemble du Système

```
┌─────────────────────────────────────────────────────────────────┐
│                    SYSTÈME VOITURE AUTONOME                      │
└─────────────────────────────────────────────────────────────────┘

                    [Batterie 7.4V Li-Po / 6V AA]
                              │
                        [Interrupteur]
                              │
                    ┌─────────┴─────────┐
                    │                   │
                    ▼                   ▼
            [Driver L298N]        [Régulateur 5V]
                    │                   │
            ┌───────┴────────┐         │
            ▼                ▼          ▼
    [Moteur Gauche]  [Moteur Droit]  [Arduino]
                                         │
                        ┌────────────────┼────────────────┐
                        ▼                ▼                ▼
                  [Capteurs US]     [LEDs]          [Bouton]
```

## Schéma de Brochage Détaillé

### Arduino Uno - Vue des Pins

```
         ARDUINO UNO R3
    ┌─────────────────────┐
    │  ╔═══════════════╗  │
    │  ║   ATMEGA328   ║  │
    │  ╚═══════════════╝  │
    │                     │
    │ DIGITAL PINS        │
D13 │ ●  (LED_STATUS)     │ +5V  ●
D12 │ ●  (M_R_BACK)       │ GND  ●
D11 │ ●  (M_R_FWD)        │ GND  ●
D10 │ ●  (M_L_SPEED)      │ Vin  ●
D9  │ ●  (M_L_BACK)       │      │
D8  │ ●  (M_L_FWD)        │ A0   ● (LED_ALERT)
D7  │ ●  (ECHO_RIGHT)     │ A1   ● (IR_LEFT)
D6  │ ●  (TRIG_RIGHT)     │ A2   ● (IR_CENTER)
D5  │ ●  (ECHO_LEFT)      │ A3   ● (IR_RIGHT)
D4  │ ●  (TRIG_LEFT)      │ A4   ● (EMERGENCY_STOP)
D3  │ ●  (ECHO_FRONT)     │ A5   ●
D2  │ ●  (TRIG_FRONT)     │      │
D1  │ ●  (TX)             │ AREF ●
D0  │ ●  (RX)             │ RESET●
    └─────────────────────┘
```

## Connexions par Sous-Système

### 1. Alimentation

```
BATTERIE (7.4V Li-Po ou 6V AA)
    │
    ├─── [+] ──┬── [Interrupteur] ──┬─→ L298N (12V/VCC)
    │          │                     │
    │          └─→ [Fusible 2A optionnel]
    │
    └─── [-] ─────────────────────────→ L298N (GND)


L298N RÉGULATEUR 5V
    │
    ├─── [5V OUT] ──────────────────→ Arduino (5V pin)
    │
    └─── [GND] ─────────────────────→ Arduino (GND pin)

Note: Le jumper 5V sur L298N doit être en place pour activer
      le régulateur intégré 5V.
```

#### Table de Connexions Alimentation

| Source | Pin Source | → | Destination | Pin Destination | Câble |
|--------|-----------|---|-------------|----------------|-------|
| Batterie | (+) | → | Interrupteur | IN | Rouge |
| Interrupteur | OUT | → | L298N | 12V/VCC | Rouge |
| Batterie | (-) | → | L298N | GND | Noir |
| L298N | 5V OUT | → | Arduino | 5V | Rouge |
| L298N | GND | → | Arduino | GND | Noir |

### 2. Driver Moteur L298N

```
ARDUINO                             L298N
┌─────────┐                     ┌──────────┐
│   D8    ├────────────────────→│   IN1    │
│   D9    ├────────────────────→│   IN2    │
│   D10   ├────────────────────→│   ENA    │  (Jumper retiré!)
│   D11   ├────────────────────→│   IN3    │
│   D12   ├────────────────────→│   IN4    │
│   D13   ├────────────────────→│   ENB    │  (Jumper retiré!)
│   GND   ├────────────────────→│   GND    │
└─────────┘                     └──────────┘

L298N                           MOTEURS
┌──────────┐                  ┌────────────┐
│  OUT1    ├─────────────────→│ Moteur G + │
│  OUT2    ├─────────────────→│ Moteur G - │
│  OUT3    ├─────────────────→│ Moteur D + │
│  OUT4    ├─────────────────→│ Moteur D - │
└──────────┘                  └────────────┘
```

#### Table de Connexions L298N

| Arduino Pin | → | L298N Pin | Fonction |
|-------------|---|-----------|----------|
| D8 | → | IN1 | Moteur Gauche Avant |
| D9 | → | IN2 | Moteur Gauche Arrière |
| D10 (PWM) | → | ENA | Vitesse Moteur Gauche |
| D11 | → | IN3 | Moteur Droit Avant |
| D12 | → | IN4 | Moteur Droit Arrière |
| D13 (PWM) | → | ENB | Vitesse Moteur Droit |
| GND | → | GND | Masse commune |

| L298N | → | Moteur | Couleur Fil |
|-------|---|--------|-------------|
| OUT1 | → | Moteur G (+) | Rouge |
| OUT2 | → | Moteur G (-) | Noir |
| OUT3 | → | Moteur D (+) | Rouge |
| OUT4 | → | Moteur D (-) | Noir |

**IMPORTANT**: Retirer les jumpers ENA et ENB sur le L298N pour permettre le contrôle PWM de la vitesse.

### 3. Capteurs Ultrasoniques HC-SR04

```
Capteur AVANT (HC-SR04)
┌──────────────────┐
│  VCC  │  5V      ├──────→ Arduino 5V
│  TRIG │  D2      ├──────→ Arduino D2
│  ECHO │  D3      ├──────→ Arduino D3
│  GND  │  GND     ├──────→ Arduino GND
└──────────────────┘

Capteur GAUCHE (HC-SR04)
┌──────────────────┐
│  VCC  │  5V      ├──────→ Arduino 5V
│  TRIG │  D4      ├──────→ Arduino D4
│  ECHO │  D5      ├──────→ Arduino D5
│  GND  │  GND     ├──────→ Arduino GND
└──────────────────┘

Capteur DROIT (HC-SR04)
┌──────────────────┐
│  VCC  │  5V      ├──────→ Arduino 5V
│  TRIG │  D6      ├──────→ Arduino D6
│  ECHO │  D7      ├──────→ Arduino D7
│  GND  │  GND     ├──────→ Arduino GND
└──────────────────┘
```

#### Table de Connexions Capteurs US

| Capteur | Pin Capteur | Arduino Pin | Fonction |
|---------|-------------|-------------|----------|
| **Avant** | VCC | 5V | Alimentation |
| | TRIG | D2 | Déclencheur |
| | ECHO | D3 | Écho reçu |
| | GND | GND | Masse |
| **Gauche** | VCC | 5V | Alimentation |
| | TRIG | D4 | Déclencheur |
| | ECHO | D5 | Écho reçu |
| | GND | GND | Masse |
| **Droit** | VCC | 5V | Alimentation |
| | TRIG | D6 | Déclencheur |
| | ECHO | D7 | Écho reçu |
| | GND | GND | Masse |

### 4. LEDs Indicateurs

```
LED STATUT (Verte)
┌─────────────────────────────────┐
│ Arduino D13 ──→ [R 220Ω] ──→ LED+ ──→ GND
└─────────────────────────────────┘

LED ALERTE (Rouge)
┌─────────────────────────────────┐
│ Arduino A0 ──→ [R 220Ω] ──→ LED+ ──→ GND
└─────────────────────────────────┘

Note: Cathode (-) vers GND, Anode (+) vers résistance
```

#### Schéma Détaillé LED

```
         Arduino Pin
              │
              │
              ▼
         [ Résistance ]
          220Ω - 330Ω
              │
              │
              ▼
         ┌────┴────┐
         │   LED   │  (Anode - longue patte)
         └────┬────┘
              │
              ▼
            [GND]
```

#### Table de Connexions LEDs

| LED | Arduino Pin | → Résistance | → LED | → GND |
|-----|-------------|--------------|-------|-------|
| Statut (Verte) | D13 | 220Ω | Anode (+) | Cathode (-) |
| Alerte (Rouge) | A0 | 220Ω | Anode (+) | Cathode (-) |

### 5. Bouton Arrêt d'Urgence

```
BOUTON AVEC PULL-UP INTERNE
┌──────────────────────────────────┐
│                                  │
│  Arduino A4 ───┬──── [Bouton] ───┤
│                │                 │
│          [Pull-up interne]      GND
│             activé              │
└──────────────────────────────────┘

État normal: HIGH (pull-up)
État appuyé: LOW (connecté à GND)
```

#### Table de Connexions Bouton

| Composant | Pin | → | Destination |
|-----------|-----|---|-------------|
| Bouton | Terminal 1 | → | Arduino A4 |
| Bouton | Terminal 2 | → | GND |

**Note**: Le pull-up interne est activé dans le code avec `pinMode(EMERGENCY_STOP, INPUT_PULLUP);`

### 6. Capteurs IR (Optionnels - Suivi de Ligne)

```
Capteurs IR pour détection de ligne
┌────────────────────────────────┐
│ IR GAUCHE   (TCRT5000)         │
│   VCC  ──→  Arduino 5V         │
│   GND  ──→  Arduino GND        │
│   OUT  ──→  Arduino A1         │
└────────────────────────────────┘
┌────────────────────────────────┐
│ IR CENTRE   (TCRT5000)         │
│   VCC  ──→  Arduino 5V         │
│   GND  ──→  Arduino GND        │
│   OUT  ──→  Arduino A2         │
└────────────────────────────────┘
┌────────────────────────────────┐
│ IR DROIT    (TCRT5000)         │
│   VCC  ──→  Arduino 5V         │
│   GND  ──→  Arduino GND        │
│   OUT  ──→  Arduino A3         │
└────────────────────────────────┘
```

## Schéma Complet - Vue d'Ensemble

```
                           SYSTÈME COMPLET

    ┌──────────────────────────────────────────────────────────┐
    │                      BATTERIE 7.4V                        │
    └────────────┬─────────────────────────────────────────────┘
                 │
           [Interrupteur]
                 │
        ┌────────┴────────┐
        │                 │
    ┌───▼───┐        ┌────▼─────┐
    │ L298N │        │ Arduino  │◄──── USB (programmation)
    │       │        │   Uno    │
    │ Motor │        │          │
    │ Driver│◄───────┤  Ctrl    │
    └───┬───┘        └────┬─────┘
        │                 │
        │      ┌──────────┼──────────────────────┐
        │      │          │                      │
    ┌───▼──┐ ┌─▼──┐  ┌───▼────┐           ┌─────▼─────┐
    │Motor │ │Motor│  │Capteurs│           │  LEDs &   │
    │  G   │ │  D  │  │  US x3 │           │  Boutons  │
    └──────┘ └─────┘  └────────┘           └───────────┘
```

## Liste Complète des Connexions

### Table Récapitulative Globale

| # | Source | Pin | Destination | Pin | Type Câble | Notes |
|---|--------|-----|-------------|-----|------------|-------|
| **ALIMENTATION** |
| 1 | Batterie | (+) | Interrupteur | IN | Rouge épais | Puissance |
| 2 | Interrupteur | OUT | L298N | 12V | Rouge épais | Puissance |
| 3 | Batterie | (-) | L298N | GND | Noir épais | Puissance |
| 4 | L298N | 5V | Arduino | 5V | Rouge fin | Signal |
| 5 | L298N | GND | Arduino | GND | Noir fin | Signal |
| **MOTEURS** |
| 6 | Arduino | D8 | L298N | IN1 | Dupont M-M | Signal |
| 7 | Arduino | D9 | L298N | IN2 | Dupont M-M | Signal |
| 8 | Arduino | D10 | L298N | ENA | Dupont M-M | PWM |
| 9 | Arduino | D11 | L298N | IN3 | Dupont M-M | Signal |
| 10 | Arduino | D12 | L298N | IN4 | Dupont M-M | Signal |
| 11 | Arduino | D13 | L298N | ENB | Dupont M-M | PWM |
| 12 | L298N | OUT1 | Moteur G | (+) | Câble moteur | Puissance |
| 13 | L298N | OUT2 | Moteur G | (-) | Câble moteur | Puissance |
| 14 | L298N | OUT3 | Moteur D | (+) | Câble moteur | Puissance |
| 15 | L298N | OUT4 | Moteur D | (-) | Câble moteur | Puissance |
| **CAPTEUR AVANT** |
| 16 | Arduino | 5V | US Avant | VCC | Rouge Dupont | Alim |
| 17 | Arduino | GND | US Avant | GND | Noir Dupont | Masse |
| 18 | Arduino | D2 | US Avant | TRIG | Dupont | Signal |
| 19 | Arduino | D3 | US Avant | ECHO | Dupont | Signal |
| **CAPTEUR GAUCHE** |
| 20 | Arduino | 5V | US Gauche | VCC | Rouge Dupont | Alim |
| 21 | Arduino | GND | US Gauche | GND | Noir Dupont | Masse |
| 22 | Arduino | D4 | US Gauche | TRIG | Dupont | Signal |
| 23 | Arduino | D5 | US Gauche | ECHO | Dupont | Signal |
| **CAPTEUR DROIT** |
| 24 | Arduino | 5V | US Droit | VCC | Rouge Dupont | Alim |
| 25 | Arduino | GND | US Droit | GND | Noir Dupont | Masse |
| 26 | Arduino | D6 | US Droit | TRIG | Dupont | Signal |
| 27 | Arduino | D7 | US Droit | ECHO | Dupont | Signal |
| **INTERFACES** |
| 28 | Arduino | D13 | Résistance | - | Dupont | LED verte |
| 29 | Résistance | - | LED verte | (+) | Câble court | - |
| 30 | LED verte | (-) | Arduino | GND | Câble court | - |
| 31 | Arduino | A0 | Résistance | - | Dupont | LED rouge |
| 32 | Résistance | - | LED rouge | (+) | Câble court | - |
| 33 | LED rouge | (-) | Arduino | GND | Câble court | - |
| 34 | Arduino | A4 | Bouton | T1 | Dupont | Pull-up int |
| 35 | Bouton | T2 | Arduino | GND | Dupont | - |

## Points de Vérification

### Avant Mise Sous Tension

- [ ] Toutes les masses (GND) sont connectées ensemble
- [ ] Pas de court-circuit entre (+) et (-)
- [ ] Polarités correctes pour tous les composants
- [ ] Jumpers ENA/ENB retirés sur L298N
- [ ] Batterie chargée
- [ ] Interrupteur en position OFF

### Mesures au Multimètre

| Point de Test | Valeur Attendue | Notes |
|---------------|-----------------|-------|
| Tension batterie | 6-8.4V | Selon type |
| L298N 12V input | = Batterie | Quand ON |
| L298N 5V output | 4.8-5.2V | Régulé |
| Arduino 5V pin | 4.8-5.2V | Régulé |
| Arduino GND - Batterie GND | 0V | Continuité |

## Conseils de Câblage

1. **Coder par couleurs**:
   - Rouge: Toutes alimentations positives
   - Noir: Toutes masses (GND)
   - Jaune: Signaux capteurs
   - Bleu: Contrôles moteurs
   - Vert: Entrées utilisateur

2. **Organiser spatialement**:
   - Grouper les fils par fonction
   - Utiliser des serre-câbles
   - Laisser un peu de mou pour mouvements

3. **Sécuriser**:
   - Souder les connexions critiques (puissance)
   - Utiliser de la gaine thermorétractable
   - Isoler tous les conducteurs nus

4. **Tester progressivement**:
   - Alimentation seule d'abord
   - Ajouter Arduino
   - Ajouter capteurs un par un
   - Ajouter moteurs en dernier

## Fichiers Fritzing (À Créer)

Les schémas Fritzing seront ajoutés dans:
- `schemas/fritzing/voiture_autonome.fzz`
- Exports: PNG, PDF, SVG

## Notes Finales

- Toujours débrancher la batterie lors des modifications
- Vérifier TOUTES les connexions avant chaque test
- Garder un multimètre à portée de main
- Documenter toute modification du schéma
