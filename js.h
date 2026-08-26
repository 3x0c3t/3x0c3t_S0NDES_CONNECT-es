#ifndef JS_H
#define JS_H

const char JS_PAGE[] PROGMEM = R"rawliteral(

async function api(url)
{
    const separator =
        url.includes("?")
            ? "&"
            : "?";

    const response =
        await fetch(
            url +
            separator +
            "t=" +
            Date.now(),
            {
                method: "GET",
                cache: "no-store"
            }
        );

    if (!response.ok)
    {
        throw new Error(
            "HTTP " +
            response.status
        );
    }

    return await response.json();
}


async function updateStatus()
{
    try
    {
        const data =
            await api("/api/status");

        const element =
            document.getElementById("status");

        if (!element)
        {
            return;
        }

        element.innerHTML =
            "<p>WiFi : " +
            (
                data.wifi
                    ? '<span class="ok">CONNECTÉ</span>'
                    : '<span class="error">ERREUR</span>'
            ) +
            "</p>" +

            "<p>SSID : <strong>" +
            (data.ssid || "-") +
            "</strong></p>" +

            "<p>IP : <strong>" +
            (data.ip || "-") +
            "</strong></p>" +

            "<p>Signal : " +
            (data.rssi ?? "-") +
            " dBm</p>" +

            "<p>Uptime : " +
            Math.floor(
                (data.uptime || 0) / 1000
            ) +
            " s</p>";
    }
    catch (error)
    {
        console.warn(
            "ESP temporairement inaccessible",
            error
        );

        const element =
            document.getElementById("status");

        if (element)
        {
            element.innerHTML =
                '<span class="error">' +
                "ESP temporairement inaccessible" +
                "</span>";
        }
    }
}


const DEFAULT_SETPOINT = 25.0;


function getSetpoint(index)
{
    const stored =
        localStorage.getItem(
            "sensorSetpoint_" + index
        );

    if (stored === null)
    {
        return DEFAULT_SETPOINT;
    }

    const value =
        Number(stored);

    if (!Number.isFinite(value))
    {
        return DEFAULT_SETPOINT;
    }

    return value;
}


function saveSetpoint(index, value)
{
    let temperature =
        Number(value);

    if (!Number.isFinite(temperature))
    {
        temperature =
            DEFAULT_SETPOINT;
    }

    temperature =
        Math.max(
            -55,
            Math.min(
                125,
                temperature
            )
        );

    temperature =
        Math.round(
            temperature * 10
        ) / 10;

    localStorage.setItem(
        "sensorSetpoint_" + index,
        temperature
    );

    return temperature;
}


function changeSetpoint(index, delta)
{
    const current =
        getSetpoint(index);

    saveSetpoint(
        index,
        current + delta
    );

    updateTemperatures();
}


function setSensorSetpoint(index, value)
{
    const temperature =
        saveSetpoint(
            index,
            value
        );

    const input =
        document.getElementById(
            "setpoint_" + index
        );

    if (input)
    {
        input.value =
            temperature.toFixed(1);
    }

    updateTemperatures();
}


function getSensorState(
    temperature,
    setpoint
)
{
    if (!Number.isFinite(temperature))
    {
        return {
            className: "state-gray",
            label: "INDISPONIBLE"
        };
    }

    const difference =
        Math.abs(
            temperature - setpoint
        );

    if (difference >= 3)
    {
        return {
            className: "state-red",
            label: "ALERTE"
        };
    }

    if (difference >= 1)
    {
        return {
            className: "state-orange",
            label: "ATTENTION"
        };
    }

    return {
        className: "state-green",
        label: "NORMAL"
    };
}


async function updateTemperatures()
{
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
                "Format températures invalide"
            );
        }

        const element =
            document.getElementById(
                "temperatures"
            );

        if (!element)
        {
            return;
        }

        let html = "";

        let normalCount = 0;
        let warningCount = 0;
        let alertCount = 0;

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

            const setpoint =
                getSetpoint(i);

            const state =
                getSensorState(
                    temperature,
                    setpoint
                );

            if (
                state.className ===
                "state-green"
            )
            {
                normalCount++;
            }
            else if (
                state.className ===
                "state-orange"
            )
            {
                warningCount++;
            }
            else if (
                state.className ===
                "state-red"
            )
            {
                alertCount++;
            }

            const valid =
                Number.isFinite(
                    temperature
                );

            const temperatureText =
                valid
                    ? temperature.toFixed(2)
                    : "--";

            const difference =
                valid
                    ? temperature - setpoint
                    : 0;

            const differenceText =
                valid
                    ? (
                        difference > 0
                            ? "+"
                            : ""
                    ) +
                    difference.toFixed(2) +
                    " °C"
                    : "--";

            const absoluteDifference =
                valid
                    ? Math.abs(difference)
                    : 0;

            const barWidth =
                Math.min(
                    100,
                    Math.max(
                        3,
                        absoluteDifference /
                        3 *
                        100
                    )
                );

            html +=
                '<article class="sensor-card ' +
                state.className +
                '">' +

                    '<div class="sensor-header">' +

                        '<div class="sensor-name">' +

                            '<span class="sensor-icon">' +
                            "🌡️" +
                            "</span>" +

                            "S" +
                            (i + 1) +

                        "</div>" +

                        '<div class="sensor-state">' +
                        state.label +
                        "</div>" +

                    "</div>" +

                    '<div class="sensor-temperature">' +

                        '<span class="sensor-temperature-value">' +
                        temperatureText +
                        "</span>" +

                        '<span class="sensor-temperature-unit">' +
                        "°C" +
                        "</span>" +

                    "</div>" +

                    '<div class="sensor-difference">' +

                        "<span>Écart à la consigne</span>" +

                        "<strong>" +
                        differenceText +
                        "</strong>" +

                    "</div>" +

                    '<div class="sensor-bar">' +

                        '<div ' +
                        'class="sensor-bar-fill" ' +
                        'style="width:' +
                        barWidth +
                        '%"' +
                        "></div>" +

                    "</div>" +

                    '<div class="sensor-setpoint">' +

                        '<div class="sensor-setpoint-label">' +
                        "CONSIGNE" +
                        "</div>" +

                        '<div class="setpoint-control">' +

                            '<button ' +
                            'class="setpoint-button" ' +
                            'type="button" ' +
                            'onclick="changeSetpoint(' +
                            i +
                            ', -0.5)"' +
                            ">" +
                            "−" +
                            "</button>" +

                            '<input ' +
                            'class="setpoint-input" ' +
                            'id="setpoint_' +
                            i +
                            '" ' +
                            'type="number" ' +
                            'step="0.5" ' +
                            'min="-55" ' +
                            'max="125" ' +
                            'value="' +
                            setpoint.toFixed(1) +
                            '" ' +
                            'onchange="setSensorSetpoint(' +
                            i +
                            ', this.value)"' +
                            ">" +

                            '<button ' +
                            'class="setpoint-button" ' +
                            'type="button" ' +
                            'onclick="changeSetpoint(' +
                            i +
                            ', 0.5)"' +
                            ">" +
                            "+" +
                            "</button>" +

                        "</div>" +

                    "</div>" +

                "</article>";
        }

        element.innerHTML =
            html;

        updateSensorSummary(
            normalCount,
            warningCount,
            alertCount
        );
    }
    catch (error)
    {
        console.warn(
            "Températures indisponibles",
            error
        );

        const element =
            document.getElementById(
                "temperatures"
            );

        if (element)
        {
            element.innerHTML =
                '<span class="error">' +
                "Températures temporairement indisponibles" +
                "</span>";
        }
    }
}


function updateSensorSummary(
    normal,
    warning,
    alert
)
{
    const element =
        document.getElementById(
            "sensorSummary"
        );

    if (!element)
    {
        return;
    }

    const total =
        normal +
        warning +
        alert;

    if (total === 0)
    {
        element.textContent =
            "--";

        return;
    }

    if (alert > 0)
    {
        element.innerHTML =
            '<span class="error">' +
            alert +
            " alerte" +
            (
                alert > 1
                    ? "s"
                    : ""
            ) +
            "</span>";

        return;
    }

    if (warning > 0)
    {
        element.innerHTML =
            '<span style="color:#f59e0b">' +
            warning +
            " attention" +
            (
                warning > 1
                    ? "s"
                    : ""
            ) +
            "</span>";

        return;
    }

    element.innerHTML =
        '<span class="ok">' +
        normal +
        " sonde" +
        (
            normal > 1
                ? "s"
                : ""
        ) +
        " normale" +
        (
            normal > 1
                ? "s"
                : ""
        ) +
        "</span>";
}


async function led(color)
{
    try
    {
        await api(
            "/api/led?color=" +
            encodeURIComponent(color)
        );
    }
    catch (error)
    {
        console.error(
            "Erreur LED :",
            error
        );
    }
}


async function buzzer(action)
{
    try
    {
        await api(
            "/api/buzzer?action=" +
            encodeURIComponent(action)
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

    try
    {
        await api(
            "/api/reboot"
        );
    }
    catch (error)
    {
    }

    const element =
        document.getElementById(
            "status"
        );

    if (element)
    {
        element.innerHTML =
            '<span class="ok">' +
            "Redémarrage en cours..." +
            "</span>";
    }
}


function rebootESP()
{
    reboot();
}


let refreshInterval = 5;
let refreshTimer = null;
let refreshBusy = false;


function getRefreshInterval()
{
    const input =
        document.getElementById(
            "refreshInterval"
        );

    if (!input)
    {
        return 5;
    }

    let value =
        parseInt(
            input.value,
            10
        );

    if (!Number.isFinite(value))
    {
        value = 5;
    }

    return Math.max(
        1,
        Math.min(
            60,
            value
        )
    );
}


async function refreshAll()
{
    if (refreshBusy)
    {
        return;
    }

    refreshBusy = true;

    try
    {
        await updateStatus();
        await updateTemperatures();
    }
    finally
    {
        refreshBusy = false;
    }
}


function startRefreshTimer()
{
    if (
        refreshTimer !== null
    )
    {
        clearTimeout(
            refreshTimer
        );
    }

    refreshInterval =
        getRefreshInterval();

    async function loop()
    {
        await refreshAll();

        refreshInterval =
            getRefreshInterval();

        refreshTimer =
            setTimeout(
                loop,
                refreshInterval * 1000
            );
    }

    refreshTimer =
        setTimeout(
            loop,
            refreshInterval * 1000
        );
}


function changeRefreshInterval()
{
    refreshInterval =
        getRefreshInterval();

    localStorage.setItem(
        "refreshInterval",
        refreshInterval
    );

    startRefreshTimer();
}


function restoreRefreshInterval()
{
    const stored =
        localStorage.getItem(
            "refreshInterval"
        );

    if (stored === null)
    {
        return;
    }

    const input =
        document.getElementById(
            "refreshInterval"
        );

    if (input)
    {
        input.value =
            Math.max(
                1,
                Math.min(
                    60,
                    Number(stored)
                )
            );
    }
}


async function init()
{
    restoreRefreshInterval();

    await refreshAll();

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