/*
 * ============================================================
 * S0NDES_CONNECTEES
 * ============================================================
 *
 * VERSION EN COURS :
 * v1.2 - DEBUG WIFI / SERVEUR HTTP
 *
 * ============================================================
 * OBJECTIF DE CETTE VERSION
 * ============================================================
 *
 * Le système fonctionne correctement côté :
 *
 * - ESP8266
 * - OLED
 * - LEDs
 * - DS18B20
 * - conversions de température
 *
 * Les températures sont actuellement stables.
 *
 * Exemple :
 *
 * S1 : 23.38
 * S2 : 24.00
 * S3 : 22.69
 *
 * ------------------------------------------------------------
 * PROBLEME ACTUEL
 * ------------------------------------------------------------
 *
 * La connexion WiFi est instable côté serveur HTTP.
 *
 * L'ESP reste parfois joignable :
 *
 * - ping OK
 * - /script.js OK
 * - /api/status OK
 *
 * mais certaines requêtes HTTP :
 *
 * - timeout
 * - connection refused
 * - connexion impossible
 *
 * Le navigateur a également présenté :
 *
 * ERR_CONNECTION_REFUSED
 * ERR_CONTENT_LENGTH_MISMATCH
 *
 * ------------------------------------------------------------
 * OBJECTIFS DES TESTS
 * ------------------------------------------------------------
 *
 * 1. Vérifier que le WiFi reste connecté.
 *
 * 2. Vérifier que le serveur HTTP reste disponible.
 *
 * 3. Vérifier que server.handleClient() est appelé
 *    suffisamment souvent.
 *
 * 4. Vérifier qu'une opération bloquante ne monopolise
 *    l'ESP8266.
 *
 * 5. Vérifier la stabilité des requêtes :
 *
 *      /api/status
 *      /api/temperatures
 *      /api/led
 *      /api/buzzer
 *      /api/reboot
 *
 * 6. Vérifier que les ressources HTML / CSS / JS sont
 *    transmises intégralement.
 *
 * 7. Identifier si les problèmes viennent :
 *
 *      - du WiFi
 *      - du serveur HTTP
 *      - du traitement des températures
 *      - d'une fonction bloquante
 *      - de la gestion des clients HTTP
 *
 * ------------------------------------------------------------
 * TEST IMPORTANT
 * ------------------------------------------------------------
 *
 * Les conversions DS18B20 sont volontairement observées
 * avec des messages :
 *
 *      CONVERSION START
 *      S1
 *      S2
 *      S3
 *      CONVERSION END
 *
 * afin de vérifier si elles perturbent le serveur HTTP.
 *
 * ------------------------------------------------------------
 * ETAT DU PROJET
 * ------------------------------------------------------------
 *
 * WiFi :
 *      A TESTER
 *
 * Serveur HTTP :
 *      A TESTER
 *
 * API :
 *      A TESTER
 *
 * Températures :
 *      FONCTIONNELLES
 *
 * LEDs :
 *      FONCTIONNELLES
 *
 * Buzzer :
 *      FONCTIONNEL
 *
 * Reboot HTTP :
 *      IMPLEMENTE
 *
 * ============================================================
 */


#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "config.h"

#include "oled.h"
#include "bootscreen.h"

#include "leds.h"
#include "buzzer.h"
#include "wifi.h"
#include "temperature.h"
#include "webserver.h"


// ============================================================
// SETUP
// ============================================================

void setup()
{
    // --------------------------------------------------------
    // SERIAL
    // --------------------------------------------------------

    Serial.begin(
        SERIAL_BAUDRATE
    );

    delay(100);

    Serial.println();
    Serial.println();
    Serial.println("==============================");
    Serial.println("S0NDES_CONNECTEES");
    Serial.println("DEMARRAGE");
    Serial.println("==============================");


    // --------------------------------------------------------
    // OLED
    // --------------------------------------------------------

    oledInit();


    // --------------------------------------------------------
    // LEDS
    // --------------------------------------------------------

    ledsInit();


    // --------------------------------------------------------
    // TEST LEDS
    // --------------------------------------------------------

    ledsTest();


    // --------------------------------------------------------
    // BUZZER
    // --------------------------------------------------------

    buzzerInit();


    // --------------------------------------------------------
    // BOOT SCREEN
    // --------------------------------------------------------

    bootScreen();


    // --------------------------------------------------------
    // TEMPERATURES
    // --------------------------------------------------------

    temperatureInit();


    // --------------------------------------------------------
    // WIFI
    // --------------------------------------------------------

    wifiInit();


    // --------------------------------------------------------
    // SERVEUR WEB
    // --------------------------------------------------------

    /*
     * Le serveur HTTP doit être initialisé uniquement
     * après la connexion WiFi.
     *
     * Cela permet de garantir que l'ESP possède déjà
     * une adresse IP avant de commencer à accepter
     * les connexions HTTP.
     */

    if (WiFi.status() == WL_CONNECTED)
    {
        webserverInit();
    }
    else
    {
        Serial.println();
        Serial.println("==============================");
        Serial.println("SERVEUR WEB NON DEMARRE");
        Serial.println("WIFI NON CONNECTE");
        Serial.println("==============================");
    }


    // --------------------------------------------------------
    // FIN INITIALISATION
    // --------------------------------------------------------

    Serial.println();
    Serial.println("==============================");
    Serial.println("=== ! SYSTEME PRET ! ===");
    Serial.println("==============================");
}


// ============================================================
// LOOP
// ============================================================

void loop()
{
    // --------------------------------------------------------
    // SERVEUR HTTP
    // --------------------------------------------------------
    //
    // IMPORTANT :
    //
    // server.handleClient() doit être exécuté très
    // régulièrement afin que l'ESP puisse traiter
    // les requêtes HTTP.
    //
    // --------------------------------------------------------

    webserverLoop();


    // --------------------------------------------------------
    // TEMPERATURES
    // --------------------------------------------------------
    //
    // Lecture des DS18B20.
    //
    // Cette fonction est actuellement surveillée car
    // les conversions sont susceptibles de bloquer
    // temporairement le traitement HTTP.
    //
    // --------------------------------------------------------

    readTemperatures();


    // --------------------------------------------------------
    // WIFI
    // --------------------------------------------------------
    //
    // Vérification de l'état de la connexion.
    //
    // Pour cette phase de debug, on ne relance pas
    // automatiquement wifiInit().
    //
    // L'objectif est d'abord d'observer précisément
    // le comportement de la connexion.
    //
    // --------------------------------------------------------

    if (WiFi.status() != WL_CONNECTED)
    {
        /*
         * Pas de reconnexion automatique ici pour le moment.
         *
         * Une reconnexion avec une boucle d'attente pourrait
         * bloquer à nouveau le serveur HTTP.
         *
         * Cette partie sera traitée dans une prochaine étape
         * après identification de la cause des pertes.
         */
    }


    // --------------------------------------------------------
    // OTA / AUTRES SERVICES
    // --------------------------------------------------------
    //
    // À compléter ici si le projet utilise des services
    // nécessitant une boucle régulière.
    //
    // --------------------------------------------------------


    // --------------------------------------------------------
    // PETITE PAUSE
    // --------------------------------------------------------
    //
    // Évite une boucle totalement agressive tout en gardant
    // une fréquence de traitement élevée.
    //
    // --------------------------------------------------------

    yield();
}