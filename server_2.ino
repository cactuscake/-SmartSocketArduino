
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D7 // пин к которому подключен датчик температуры DS18b20
#define  RELAY1 D1 // пин к которому подключено реле
#define  RELAY2 D2
#define  RELAY3 D3
#define  RELAY4 D4
bool relay1  = true; // разомкнуто для низкоуровнего реле при включении микроконтроллера.
bool relay2  = true;
bool relay3  = true;
bool relay4  = true;
float temp;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


const char* ssid = "Sanya";
const char* password = "00000000";

ESP8266WebServer server(80);

void setup() {

  Serial.begin(115200);

  // Инициализация выхода реле
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, relay1); // при включении микроконтроллера низкоуровневое реле разомкнуто
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY2, relay2);
  pinMode(RELAY3, OUTPUT);
  digitalWrite(RELAY3, relay3);
  pinMode(RELAY4, OUTPUT);
  digitalWrite(RELAY4, relay4);

  // Инициализация датчика температуры DS18b20
  sensors.begin();
  
  // Подлючение к WiFi
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    // Запуск WEB-сервера
        server.on ( "/", HTTP);
    server.onNotFound ( HTTP);
    server.begin();
    Serial.println ();
    Serial.print( "HTTP server start! Open http://");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.printf("WiFi started is fail");
  }

}


void loop() {
  server.handleClient();
  delay(50);
}


/*
   Оработчик главной страницы сервера
*/
void HTTP(void) {
  bool stat1 = false;
   sensors.requestTemperatures();
   temp = sensors.getTempCByIndex(0);
   
  if ( server.hasArg("stat1") ) {
    if ( strncmp(server.arg("stat1").c_str(), "1", 1) == 0 )stat1 = true;
  }
  else {
    stat1 = relay1;
  }

bool stat2 = false;
   sensors.requestTemperatures(); 
   temp = sensors.getTempCByIndex(0);
   
  if ( server.hasArg("stat2") ) {
    if ( strncmp(server.arg("stat2").c_str(), "1", 1) == 0 )stat2 = true;
  }
  else {
    stat2 = relay2;
  }

bool stat3 = false;
   sensors.requestTemperatures();
   temp = sensors.getTempCByIndex(0);
   
  if ( server.hasArg("stat3") ) {
    if ( strncmp(server.arg("stat3").c_str(), "1", 1) == 0 )stat3 = true;
  }
  else {
    stat3 = relay3;
  }

bool stat4 = false;
   sensors.requestTemperatures();
   temp = sensors.getTempCByIndex(0);
   
  if ( server.hasArg("stat4") ) {
    if ( strncmp(server.arg("stat4").c_str(), "1", 1) == 0 )stat4 = true;
  }
  else {
    stat4 = relay4;
  }



  String website = "";

  website =
    "<html>\
  <head>\
    <meta charset=\"utf-8\" />\
    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">\
    <title>WiFi control temр</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: blue; text-align: center; }\
    </style>\
  </head>\
  <body>\
    <h1 style=\"color: black;\">Умная розетка</h1>\
    <h3>\n";
    website += "\</h3>\n";

    
  if ( stat1 ) {
    website += "\
        <h3>розетка 1: Выключена</br>\
    <a style=\"color: red;\" href=\"/?stat1=0\">Включить</a></h3>\
    ";
  }
  else {
    website += "\
    <h3> розетка 1: Выключена</br>\
    <a style=\"color: red;\" href=\"/?stat1=1\">Выключить</a><h3>\
    ";
  }


if ( stat2 ) {
    website += "\
        <h3>розетка 2: Выключена</br>\
    <a style=\"color: red;\" href=\"/?stat2=0\">Включить</a></h3>\
    ";
  }
  else {
    website += "\
    <h3>розетка 2: Включена</br>\
    <a style=\"color: red;\" href=\"/?stat2=1\">Выключить</a><h3>\
    ";
  }



if ( stat3 ) {
    website += "\
        <h3>розетка 3: Выключена</br>\
    <a style=\"color: red;\" href=\"/?stat3=0\">Включить</a></h3>\
    ";
  }
  else {
    website += "\
    <h3>розетка 3: Включена</br>\
    <a style=\"color: red;\" href=\"/?stat3=1\">Выключить</a><h3>\
    ";
  }

  


if ( stat4 ) {
    website += "\
        <h3>розетка 4: Выключена</br>\
    <a style=\"color: red;\" href=\"/?stat4=0\">Включить</a></h3>\
    ";
  }
  else {
    website += "\
    <h3>розетка 4: Включена</br>\
    <a style=\"color: red;\" href=\"/?stat4=1\">Выключить</a><h3>\
    ";
  }

  server.send ( 200, "text/html", website );
  Serial.println (temp);
  if ( stat1 != relay1) {
    relay1 = stat1;
    digitalWrite(RELAY1, relay1);
    if (relay1)Serial.println("Power is ON");
    else Serial.println("Power is OFF");
  }

  //server.send ( 200, "text/html", website );
  Serial.println (temp);
  if ( stat2 != relay2 ) {
    relay2 = stat2;
    digitalWrite(RELAY2, relay2);
    if (relay2)Serial.println("Power is ON");
    else Serial.println("Power is OFF");
  }

  //server.send ( 200, "text/html", website );
  Serial.println (temp);
  if ( stat3 != relay3 ) {
    relay3 = stat3;
    digitalWrite(RELAY3, relay3);
    if (relay3)Serial.println("Power is ON");
    else Serial.println("Power is OFF");
  }

  //server.send ( 200, "text/html", website );
  Serial.println (temp);
  if ( stat4 != relay4 ) {
    relay4 = stat4;
    digitalWrite(RELAY4, relay4);
    if (relay4)Serial.println("Power is ON");
    else Serial.println("Power is OFF");
  }

}





