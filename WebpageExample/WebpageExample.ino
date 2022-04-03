/*******************************************************************
    An example sketch for interacting with an ESP32 using a 
    web interface
    
    Based on an RC Car example written by Brian Lough
    https://www.youtube.com/channel/UCezJOfu7OtqGzd5xrP3q6WA
    https://github.com/witnessmenow/simple-wifi-controlled-rc-car
 *******************************************************************/

#include <WiFiClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// These pins are used to indicate button press. They can be connected to LEDs for visualization of working code.
#define PIN1 14
#define PIN2 27
#define PIN3 26
#define PIN4 25

volatile bool BUTTONDOWNFLAG1 = false;
volatile bool BUTTONDOWNFLAG2 = false;
volatile bool BUTTONDOWNFLAG3 = false;
volatile bool BUTTONDOWNFLAG4 = false;
volatile bool BUTTONRELEASEFLAG_COMMON = false;

// ----------------
// Set your WiFi SSID and Password here
// ----------------
const char* ssid = "ssid";
const char* password = "password";

WebServer server(80);

const char *webpage = 
#include "webPage.h"
;

void handleRoot() {

  server.send(200, "text/html", webpage);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void buttondown_handler1(){
  BUTTONDOWNFLAG1 = false;
  digitalWrite(PIN1, HIGH);
}

void buttondown_handler2(){
  BUTTONDOWNFLAG2 = false;
  digitalWrite(PIN2, HIGH);
}

void buttondown_handler3(){
  BUTTONDOWNFLAG3 = false;
  digitalWrite(PIN3, HIGH);
}

void buttondown_handler4(){
  BUTTONDOWNFLAG4 = false;
  digitalWrite(PIN4, HIGH);
}

void buttonrelease_handler_common(){
  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, LOW);
  digitalWrite(PIN4, LOW);
  BUTTONRELEASEFLAG_COMMON = false;
}

void setup(void){

   pinMode(PIN1, OUTPUT);    
   pinMode(PIN2, OUTPUT);
   pinMode(PIN3, OUTPUT);
   pinMode(PIN4, OUTPUT);
   digitalWrite(PIN1, LOW);
   digitalWrite(PIN2, LOW);
   digitalWrite(PIN3, LOW);
   digitalWrite(PIN4, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("ButtonExample")) {
    Serial.println("MDNS Responder Started");
  }

  server.on("/", handleRoot);

  server.on("/up", [](){
    Serial.println("up - buttondown1");
    BUTTONDOWNFLAG1 = true;
    server.send(200, "text/plain", "up");
  });

  server.on("/down", [](){
    Serial.println("down - buttondown2");
    BUTTONDOWNFLAG2 = true;
    server.send(200, "text/plain", "down");
  });

  server.on("/right", [](){
    Serial.println("right - buttondown3");
    BUTTONDOWNFLAG3 = true;
    server.send(200, "text/plain", "right");
  });

  server.on("/left", [](){
    Serial.println("left - buttondown4");
    BUTTONDOWNFLAG4 = true;
    server.send(200, "text/plain", "left");
  });

  server.on("/buttonrelease", [](){
    Serial.println("ButtonRelease");
    BUTTONRELEASEFLAG_COMMON = true;
    server.send(200, "text/plain", "buttonrelease");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void){
  server.handleClient();
  if(BUTTONDOWNFLAG1){
    buttondown_handler1();
  }else if(BUTTONDOWNFLAG2){
    buttondown_handler2();
  }else if(BUTTONDOWNFLAG3){
    buttondown_handler3();
  }else if(BUTTONDOWNFLAG4){
    buttondown_handler4();
  }else if(BUTTONRELEASEFLAG_COMMON){
    buttonrelease_handler_common();
  }
}