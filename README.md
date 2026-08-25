# 🌡️ 3x0c3t_S0NDES_CONNECT-es

Système de sondes de température connectées basé sur **ESP8266**.

Le projet permet de mesurer des températures avec des sondes DS18B20, d'afficher les informations sur un écran OLED, de signaler l'état du système par LEDs et buzzer, de se connecter en Wi-Fi et de fournir une interface Web embarquée.

---

# 🚧 Version de développement

> **VERSION DE DÉVELOPPEMENT**
>
> Cette version `v1.2` est actuellement en cours de développement.
>
> Le fonctionnement global, l'interface OLED, l'interface Web et certaines fonctions de pilotage peuvent être **incomplets, expérimentaux ou non fonctionnels**.
>
> Le code est susceptible d'évoluer rapidement et des modifications importantes de l'architecture peuvent encore intervenir.

**Version : `v1.2-dev`**

**Date : `25 août 2026`**

**Heure de référence : `04:54`**

---

# 🎯 Objectif actuel de la v1.2

La version `v1.2` a pour objectif de transformer progressivement le système en une plateforme de surveillance et de **pilotage à distance de l'ESP8266**.

Les priorités actuelles sont :

### OLED

Ajouter au fonctionnement actuel :

- affichage du **SSID Wi-Fi utilisé** ;
- affichage de l'adresse IP ;
- conservation des informations de démarrage ;
- affichage des températures ;
- amélioration progressive de la présentation.

### Interface Web

Développer une interface permettant de piloter l'ESP8266 en direct :

- affichage de l'état du système ;
- retour d'informations ;
- modification des consignes ;
- contrôle du buzzer ;
- contrôle des LEDs ;
- redémarrage de l'ESP8266 ;
- consultation des températures ;
- informations réseau ;
- état général du système.

L'interface Web doit progressivement devenir le **panneau de contrôle principal** du système.

---

# ✨ Fonctionnalités

## Actuellement présentes

- 🌡️ Lecture des températures
- 📺 Affichage OLED
- 📡 Connexion Wi-Fi
- 🌐 Serveur Web embarqué
- 🔄 Mise à jour OTA
- 💡 Gestion des LEDs
- 🔊 Gestion du buzzer
- 🎵 Mélodie de démarrage
- 🚀 Splash screen
- 🖥️ Écran de démarrage / informations système
- 🧩 Architecture modulaire

## En développement pour v1.2

- 📶 Affichage du SSID Wi-Fi sur OLED
- 🌐 Tableau de bord Web
- 🎛️ Pilotage direct de l'ESP8266
- 💡 Pilotage des LEDs depuis le Web
- 🔊 Pilotage du buzzer depuis le Web
- 🌡️ Gestion des consignes
- ⚠️ Gestion des alertes
- 🔄 Redémarrage logiciel depuis le Web
- 📊 Retour d'état en temps réel
- 📡 Informations réseau
- 🖥️ Amélioration des écrans OLED

---

# 🧰 Matériel

## Microcontrôleur

```text
ESP8266 NodeMCU