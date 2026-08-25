# 3x0c3t_S0NDES_CONNECT-es

Système connecté de surveillance de température basé sur **ESP8266 NodeMCU**, avec affichage OLED, sondes DS18B20, Wi-Fi, serveur Web et OTA.

Projet développé par **3x0c3t**.

---

## Sommaire

- [Présentation](#présentation)
- [Fonctionnalités](#fonctionnalités)
- [Matériel](#matériel)
- [Architecture du projet](#architecture-du-projet)
- [Déroulement du démarrage](#déroulement-du-démarrage)
- [Affichage OLED](#affichage-oled)
- [LED](#led)
- [Buzzer](#buzzer)
- [Wi-Fi](#wi-fi)
- [Sondes de température](#sondes-de-température)
- [Serveur Web](#serveur-web)
- [OTA](#ota)
- [Configuration](#configuration)
- [Compilation](#compilation)
- [Installation](#installation)
- [Structure des fichiers](#structure-des-fichiers)
- [Mémoire utilisée](#mémoire-utilisée)
- [Version](#version)

---

# Présentation

**3x0c3t_S0NDES_CONNECT-es** est un système de surveillance de température connecté construit autour d'un ESP8266.

Le système permet :

- de mesurer la température avec des sondes **DS18B20** ;
- d'afficher les températures sur un écran **OLED SSD1306 128×64** ;
- de se connecter à un réseau Wi-Fi ;
- d'afficher l'adresse IP obtenue ;
- de fournir une interface Web ;
- de mettre à jour le firmware à distance avec **OTA** ;
- d'utiliser des LED pour signaler différents états ;
- d'utiliser un buzzer pour fournir des indications sonores au démarrage et lors de la connexion Wi-Fi.

---

# Fonctionnalités

## Surveillance de température

Les températures sont mesurées avec des capteurs **DS18B20** utilisant le protocole OneWire.

Les valeurs sont affichées périodiquement sur l'écran OLED.

---

## Écran OLED

L'affichage utilise :

- écran OLED SSD1306 ;
- résolution : **128 × 64 pixels** ;
- communication : **I²C** ;
- bibliothèque : **U8g2**.

L'écran est utilisé pour plusieurs étapes :

1. Splash screen ;
2. écran d'informations de démarrage ;
3. informations de connexion Wi-Fi ;
4. affichage des températures.

L'OLED constitue donc l'interface locale principale du système.

---

## Wi-Fi

Le module se connecte automatiquement au réseau configuré dans `config.h`.

En cas de connexion réussie :

- l'état Wi-Fi est indiqué ;
- l'adresse IP est affichée ;
- une séquence sonore est jouée ;
- les LED indiquent la réussite.

En cas d'échec :

- l'erreur est affichée ;
- une séquence sonore d'échec est jouée ;
- les LED indiquent l'erreur.

---

## Serveur Web

Le système démarre un serveur Web sur l'ESP8266.

Le serveur permet notamment d'accéder aux informations du système depuis un navigateur Web.

Les ressources Web sont séparées dans différents fichiers :

- `html.h`
- `css.h`
- `js.h`

---

## Mise à jour OTA

Le firmware peut être mis à jour à distance grâce à **ArduinoOTA**.

Cela permet d'éviter de reconnecter physiquement l'ESP8266 à l'ordinateur à chaque nouvelle version.

---

# Matériel

## Microcontrôleur

**ESP8266 NodeMCU**

Carte utilisée pour le développement :

```text
NodeMCU ESP8266