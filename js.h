#ifndef JS_H
#define JS_H

#include <Arduino.h>

const char JS_PAGE[] PROGMEM = R"rawliteral(

/* ============================================================
   CONFIGURATION
   ============================================================ */

const DEFAULT_REFRESH_INTERVAL = 2;
const MIN_REFRESH_INTERVAL = 1;
const MAX_REFRESH_INTERVAL = 60;

let refreshInterval =
    DEFAULT_REFRESH_INTERVAL;

let refreshTimer = null;

let temperatureRequestRunning = false;
let statusRequestRunning = false;


/* ============================================================
   API
   ============================================================ */

async function api(url)
{
    const response = await fetch(
        url,
        {
            cache: "no-store"
        }
    );

    if (!response.ok)
    {
        throw new Error(
            "HTTP " + response.status
        );
    }

    return await response.json();
}


/* ============================================================
   CONSIGNES
   ============================================================ */

function getSetpoint(index)
{
    const key =
        "sensor_setpoint_" + index;

    const stored =
        localStorage.getItem(key);

    if (stored === null)
    {
        return 25.0;
    }

    const value =
        Number(stored);

    if (!Number.isFinite(value))
    {
        return 25.0;
    }

    return value;
}


function saveSetpoint(index, value)
{
    localStorage.setItem(
        "sensor_setpoint_" + index,
        value.toFixed(1)
    );
}


function changeSetpoint(index, delta)
{
    let value =
        getSetpoint(index);

    value += delta;

    /*
       Limites volontairement larges.
       La consigne reste une fonction Web
       tant qu'aucune API matérielle n'est définie.
    */

    value =
        Math.max(
            -40,
            Math.min(
                100,
                value
            )
        );

    saveSetpoint(
        index,
        value
    );

    updateTemperatures();
}


/* ============================================================
   ETAT D'UNE SONDE
   ============================================================ */

function getSensorState(
    temperature,
    setpoint
)
{
    const tolerance = 0.5;

    if (
        temperature <
        setpoint - tolerance
    )
    {
        return {
            text: "BAS",
            className: "sensor-low"
        };
    }

    if (
        temperature >
        setpoint + tolerance
    )
    {
        return {
            text: "HAUT",
            className: "sensor-high"
        };
    }

    return {
        text: "OK",
        className: "sensor-ok"
    };
}


/* ============================================================
   ETAT DU SYSTEME
   ============================================================ */

async function updateStatus()
{
    if (statusRequestRunning)
    {
        return;
    }

    statusRequestRunning = true;

    try
    {
        const data =
            await api(
                "/api/status"
            );

        let html = "";

        html +=
            "<p>WiFi : " +
            (
                data.wifi
                ?
                '<span class="ok">CONNECTÉ</span>'
                :
                '<span class="error">ERREUR</span>'
            ) +
            "</p>";

        html +=
            "<p>SSID : <strong>" +
            escapeHTML(
                data.ssid
            ) +
            "</strong></p>";

        html +=
            "<p>IP : <strong>" +
            escapeHTML(
                data.ip
            ) +
            "</strong></p>";

        html +=
            "<p>Signal : " +
            Number(
                data.rssi
            ) +
            " dBm</p>";

        html +=
            "<p>Uptime : " +
            Number(
                data.uptime
            ) +
            " s</p>";

        const element =
            document.getElementById(
                "status"
            );

        if (element)
        {
            element.innerHTML =
                html;
        }
    }
    catch (error)
    {
        console.error(
            "ESP temporairement inaccessible",
            error
        );

        const element =
            document.getElementById(
                "status"
            );

        if (element)
        {
            element.innerHTML =
                '<span class="error">' +
                'ESP temporairement inaccessible' +
                '</span>';
        }
    }
    finally
    {
        statusRequestRunning = false;
    }
}


/* ============================================================
   TEMPERATURES
   ============================================================ */

async function updateTemperatures()
{
    if (temperatureRequestRunning)
    {
        return;
    }

    temperatureRequestRunning = true;

    try
    {
        const data =
            await api(
                "/api/temperatures"
            );

        if (
            !data ||
            !Array.isArray(
                data.temperatures
            )
        )
        {
            throw new Error(
                "Format température invalide"
            );
        }

        let html = "";

        for (
            let i = 0;
            i < data.temperatures.length;
            i++
        )
        {
            const temperature =
                Number(
                    data.temperatures[i]
                );

            if (
                !Number.isFinite(
                    temperature
                )
            )
            {
                continue;
            }

            const setpoint =
                getSetpoint(i);

            const state =
                getSensorState(
                    temperature,
                    setpoint
                );

            html +=

                '<div class="sensor-card">' +

                    '<div class="sensor-header">' +

                        '<span class="sensor-name">' +
                            '🌡️ Sonde S' +
                            (i + 1) +
                        '</span>' +

                        '<span class="sensor-state ' +
                            state.className +
                        '">' +
                            state.text +
                        '</span>' +

                    '</div>' +

                    '<div class="sensor-temperature">' +
                        temperature.toFixed(2) +
                        ' °C' +
                    '</div>' +

                    '<div class="sensor-setpoint">' +

                        '<div>' +

                            '<div class="setpoint-label">' +
                                'Consigne' +
                            '</div>' +

                            '<div class="setpoint-value">' +
                                setpoint.toFixed(1) +
                                ' °C' +
                            '</div>' +

                        '</div>' +

                        '<div class="setpoint-buttons">' +

                            '<button ' +
                                'class="setpoint-button" ' +
                                'type="button" ' +
                                'onclick="changeSetpoint(' +
                                i +
                                ',-0.5)"' +
                            '>' +
                                '−' +
                            '</button>' +

                            '<button ' +
                                'class="setpoint-button" ' +
                                'type="button" ' +
                                'onclick="changeSetpoint(' +
                                i +
                                ',0.5)"' +
                            '>' +
                                '+' +
                            '</button>' +

                        '</div>' +

                    '</div>' +

                '</div>';
        }

        const element =
            document.getElementById(
                "temperatures"
            );

        if (element)
        {
            element.innerHTML =
                html;
        }
    }
    catch (error)
    {
        console.error(
            "Températures temporairement indisponibles",
            error
        );

        const element =
            document.getElementById(
                "temperatures"
            );

        /*
           On ne détruit pas immédiatement
           l'affichage précédent.

           Cela évite que l'interface clignote
           à chaque perte Wi-Fi.
        */

        if (
            element &&
            !element.children.length
        )
        {
            element.innerHTML =
                '<span class="error">' +
                'Températures temporairement indisponibles' +
                '</span>';
        }
    }
    finally
    {
        temperatureRequestRunning = false;
    }
}


/* ============================================================
   RAFRAICHISSEMENT
   ============================================================ */

function loadRefreshInterval()
{
    const stored =
        localStorage.getItem(
            "refresh_interval"
        );

    if (stored !== null)
    {
        const value =
            Number(stored);

        if (
            Number.isFinite(value) &&
            value >= MIN_REFRESH_INTERVAL &&
            value <= MAX_REFRESH_INTERVAL
        )
        {
            refreshInterval =
                Math.round(value);
        }
    }

    const input =
        document.getElementById(
            "refreshInterval"
        );

    if (input)
    {
        input.value =
            refreshInterval;
    }
}


function applyRefreshInterval()
{
    const input =
        document.getElementById(
            "refreshInterval"
        );

    if (!input)
    {
        return;
    }

    let value =
        Number(
            input.value
        );

    if (!Number.isFinite(value))
    {
        value =
            DEFAULT_REFRESH_INTERVAL;
    }

    value =
        Math.round(value);

    value =
        Math.max(
            MIN_REFRESH_INTERVAL,
            Math.min(
                MAX_REFRESH_INTERVAL,
                value
            )
        );

    refreshInterval =
        value;

    input.value =
        value;

    localStorage.setItem(
        "refresh_interval",
        value
    );

    startRefreshTimer();

    updateTemperatures();
}


function startRefreshTimer()
{
    if (refreshTimer !== null)
    {
        clearInterval(
            refreshTimer
        );
    }

    refreshTimer =
        setInterval(
            updateTemperatures,
            refreshInterval * 1000
        );
}


/* ============================================================
   LED
   ============================================================ */

async function led(color)
{
    try
    {
        await api(
            "/api/led?color=" +
            encodeURIComponent(
                color
            )
        );

        updateStatus();
    }
    catch (error)
    {
        console.error(
            "Erreur LED :",
            error
        );
    }
}


/* ============================================================
   BUZZER
   ============================================================ */

async function buzzer(action)
{
    try
    {
        await api(
            "/api/buzzer?action=" +
            encodeURIComponent(
                action
            )
        );
    }
    catch (error)
    {
        console.error(
            "Erreur buzzer :",
            error
        );
    }
}


/* ============================================================
   REBOOT
   ============================================================ */

async function reboot()
{
    if (
        !confirm(
            "Redémarrer l'ESP8266 ?"
        )
    )
    {
        return;
    }

    /*
       On arrête les requêtes périodiques
       avant le reboot.

       Cela évite de bombarder l'ESP
       pendant qu'il redémarre.
    */

    if (refreshTimer !== null)
    {
        clearInterval(
            refreshTimer
        );

        refreshTimer = null;
    }

    try
    {
        await fetch(
            "/api/reboot",
            {
                cache: "no-store"
            }
        );
    }
    catch (error)
    {
        /*
           Normal :
           l'ESP peut couper la connexion
           avant que fetch reçoive la réponse.
        */
    }

    const status =
        document.getElementById(
            "status"
        );

    if (status)
    {
        status.innerHTML =
            '<span class="error">' +
            'Redémarrage en cours...' +
            '</span>';
    }

    /*
       L'ESP redémarre.
       On attend avant de recommencer
       les requêtes.
    */

    setTimeout(
        function()
        {
            updateStatus();
            updateTemperatures();
            startRefreshTimer();
        },
        5000
    );
}


/*
   Compatibilité avec le HTML.
   Le bouton appelle rebootESP().
*/

function rebootESP()
{
    reboot();
}


/* ============================================================
   SECURITE HTML
   ============================================================ */

function escapeHTML(value)
{
    return String(value)
        .replace(
            /&/g,
            "&amp;"
        )
        .replace(
            /</g,
            "&lt;"
        )
        .replace(
            />/g,
            "&gt;"
        )
        .replace(
            /"/g,
            "&quot;"
        )
        .replace(
            /'/g,
            "&#039;"
        );
}


/* ============================================================
   INITIALISATION
   ============================================================ */

function init()
{
    loadRefreshInterval();

    updateStatus();

    updateTemperatures();

    /*
       L'état Wi-Fi est rafraîchi
       indépendamment des températures.
    */

    setInterval(
        updateStatus,
        5000
    );

    startRefreshTimer();
}


if (
    document.readyState ===
    "loading"
)
{
    document.addEventListener(
        "DOMContentLoaded",
        init
    );
}
else
{
    init();
}

)rawliteral";

#endif