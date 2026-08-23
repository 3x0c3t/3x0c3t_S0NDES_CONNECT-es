#include "webserver.h"

#include <ESP8266WebServer.h>

#include "globals.h"

#include "html.h"
#include "css.h"
#include "js.h"


ESP8266WebServer server(80);



void handleRoot()
{

String page=htmlPage;

page.replace("%CSS%",cssStyle);

page.replace("%JS%",jsScript);


server.send(
200,
"text/html",
page
);

}



void handleTemperature()
{

String json="{";


json+="\"count\":";
json+=sensorCount;
json+=",";


json+="\"temperatures\":[";


for(uint8_t i=0;i<sensorCount;i++)
{

json+=String(temperatures[i],2);

if(i<sensorCount-1)
json+=",";

}


json+="]}";


server.send(
200,
"application/json",
json
);

}



void webserverInit()
{

server.on("/",handleRoot);

server.on(
"/temperature",
handleTemperature
);


server.begin();


Serial.println("HTTP OK");

}



void webserverLoop()
{
server.handleClient();
}

