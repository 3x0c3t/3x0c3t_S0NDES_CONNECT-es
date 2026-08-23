# 🌡️ S0NDES_CONNECTEES

Système de sondes de température connectées basé sur **ESP8266**.

Le projet permet de mesurer la température à l'aide de sondes, d'afficher les informations sur un écran OLED, de signaler l'état du système par LEDs et buzzer, et de fournir une interface Web accessible via le réseau Wi-Fi.

**Version actuelle : `v1.0`**

---

## ✨ Fonctionnalités

* 🌡️ Lecture des températures
* 📺 Affichage sur écran OLED
* 🌐 Serveur Web embarqué
* 📡 Connexion Wi-Fi
* 🔄 Mise à jour OTA
* 💡 Gestion des LEDs d'état
* 🔊 Buzzer et mélodie de démarrage
* 🚀 Écran de démarrage `splashScreen()`
* 🧩 Code organisé en modules indépendants

---

## 🧰 Matériel

### Microcontrôleur

* ESP8266

### Capteurs

* Sondes de température compatibles avec le module `temperature`

### Affichage

* Écran OLED I²C

### Signalisation

* LED(s) d'état
* Buzzer

---

## 📁 Structure du projet

```text
S0NDES_CONNECTEES/
├── S0NDES_CONNECTEES.ino
│
├── config.h
├── defines.h
├── globals.h
├── text.h
│
├── temperature.cpp
├── temperature.h
│
├── oled.cpp
├── oled.h
│
├── wifi.cpp
├── wifi.h
│
├── webserver.cpp
├── webserver.h
│
├── ota.cpp
├── ota.h
│
├── leds.cpp
├── leds.h
│
├── buzzer.cpp
├── buzzer.h
│
├── utils.cpp
└── utils.h
```

### Organisation

| Module          | Fonction                            |
| --------------- | ----------------------------------- |
| `temperature.*` | Lecture et gestion des températures |
| `oled.*`        | Gestion de l'écran OLED             |
| `wifi.*`        | Connexion au réseau Wi-Fi           |
| `webserver.*`   | Serveur Web embarqué                |
| `ota.*`         | Mise à jour du firmware par OTA     |
| `leds.*`        | Gestion des LEDs                    |
| `buzzer.*`      | Gestion du buzzer et des sons       |
| `utils.*`       | Fonctions utilitaires               |
| `config.h`      | Configuration du système            |
| `defines.h`     | Définitions et constantes           |
| `globals.h`     | Variables globales                  |
| `text.h`        | Textes utilisés par le firmware     |

---

## 🚀 Fonctionnement

Au démarrage, le firmware initialise successivement les différents périphériques :

```text
ESP8266
   │
   ├── LEDs
   ├── Buzzer
   ├── OLED
   │    └── Splash screen
   │
   ├── Wi-Fi
   ├── OTA
   ├── Température
   └── Serveur Web
```

Une fois le système démarré, la boucle principale :

* maintient le service OTA ;
* maintient le serveur Web ;
* lit les températures périodiquement ;
* actualise l'affichage OLED.

La version `v1.0` effectue actuellement une lecture des températures toutes les **5 secondes**.

---

## 📺 Démarrage OLED

Le démarrage du système utilise :

```cpp
oledInit();
splashScreen();
```

Le splash screen est défini dans :

```text
oled.cpp
oled.h
```

Il constitue l'écran d'accueil avant le passage à l'affichage des températures.

---

## 🌐 Serveur Web

Le projet embarque un serveur Web directement sur l'ESP8266.

Les ressources de l'interface sont séparées dans :

```text
html.h
css.h
js.h
```

Cela permet de conserver l'interface Web directement dans le firmware sans dépendre d'un serveur externe.

---

## 🔄 OTA

Le firmware intègre la mise à jour **Over-The-Air (OTA)**.

Les fonctions principales sont regroupées dans :

```text
ota.cpp
ota.h
```

Le service OTA est maintenu dans la boucle principale du programme.

---

## ⚙️ Configuration

La configuration du projet se trouve principalement dans :

```text
config.h
defines.h
```

Avant de compiler le firmware, vérifier notamment les paramètres réseau et les constantes matérielles.

> ⚠️ Ne pas publier de mots de passe Wi-Fi, clés API ou autres secrets dans un dépôt GitHub public.

---

## 🔧 Compilation

Le projet est destiné à être compilé avec **Arduino IDE** ou un environnement compatible ESP8266.

Ouvrir :

```text
S0NDES_CONNECTEES.ino
```

Puis sélectionner la carte ESP8266 correspondant au matériel utilisé.

Installer les bibliothèques nécessaires aux composants utilisés par le projet avant compilation.

---

## 📌 Version v1.0

La version `v1.0` constitue la **base stable de référence du projet**.

Elle sert de point de départ pour le développement des prochaines fonctionnalités.

### État de la v1.0

* [x] Architecture modulaire
* [x] Initialisation ESP8266
* [x] LEDs
* [x] Buzzer
* [x] OLED
* [x] Splash screen
* [x] Wi-Fi
* [x] OTA
* [x] Lecture des températures
* [x] Serveur Web
* [x] Affichage périodique des températures

---

## 🛠️ Développement futur

Les prochaines versions pourront notamment faire évoluer :

* l'affichage OLED ;
* l'interface Web ;
* la gestion de plusieurs sondes ;
* les seuils d'alerte ;
* les notifications ;
* l'historique des températures ;
* la configuration depuis l'interface Web ;
* la communication entre plusieurs ESP8266 ;
* la sauvegarde persistante des paramètres.

---

## 📜 Licence

Projet personnel **3x0c3t**.

Voir les fichiers du dépôt pour les informations de licence applicables.

---

## 👤 Auteur

**3x0c3t**

GitHub :

https://github.com/3x0c3t

Projet :

https://github.com/3x0c3t/3x0c3t_S0NDES_CONNECT-es

---

**S0NDES_CONNECTEES — v1.0**
