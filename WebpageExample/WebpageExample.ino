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
#define UP_LED_PIN 14
#define DOWN_LED_PIN 27
#define RIGHT_LED_PIN 26
#define LEFT_LED_PIN 25

volatile bool UPBUTTONFLAG = false;
volatile bool DOWNBUTTONFLAG = false;
volatile bool RIGHTBUTTONFLAG = false;
volatile bool LEFTBUTTONFLAG = false;
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

void up_button_handler(){
  UPBUTTONFLAG = false;
  digitalWrite(UP_LED_PIN, !digitalRead(UP_LED_PIN)); //Toggle LED pin
}

void down_button_handler(){
  DOWNBUTTONFLAG = false;
  digitalWrite(DOWN_LED_PIN, !digitalRead(DOWN_LED_PIN)); //Toggle LED pin
}

void right_button_handler(){
  RIGHTBUTTONFLAG = false;
  digitalWrite(RIGHT_LED_PIN, !digitalRead(RIGHT_LED_PIN)); //Toggle LED pin
}

void left_button_handler(){
  LEFTBUTTONFLAG = false;
  digitalWrite(LEFT_LED_PIN, !digitalRead(LEFT_LED_PIN)); //Toggle LED pin
}

void setup(void){

   pinMode(UP_LED_PIN, OUTPUT);    
   pinMode(DOWN_LED_PIN, OUTPUT);
   pinMode(RIGHT_LED_PIN, OUTPUT);
   pinMode(LEFT_LED_PIN, OUTPUT);
   digitalWrite(UP_LED_PIN, LOW);
   digitalWrite(DOWN_LED_PIN, LOW);
   digitalWrite(RIGHT_LED_PIN, LOW);
   digitalWrite(LEFT_LED_PIN, LOW);

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
    Serial.println("up");
    UPBUTTONFLAG = true;
    server.send(200, "text/plain", "up");
  });

  server.on("/down", [](){
    Serial.println("down");
    DOWNBUTTONFLAG = true;
    server.send(200, "text/plain", "down");
  });

  server.on("/right", [](){
    Serial.println("right");
    RIGHTBUTTONFLAG = true;
    server.send(200, "text/plain", "right");
  });

  server.on("/left", [](){
    Serial.println("left");
    LEFTBUTTONFLAG = true;
    server.send(200, "text/plain", "left");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void){
  server.handleClient();
  if(UPBUTTONFLAG){
    up_button_handler();
  }else if(DOWNBUTTONFLAG){
    down_button_handler();
  }else if(RIGHTBUTTONFLAG){
    right_button_handler();
  }else if(LEFTBUTTONFLAG){
    left_button_handler();
  }
}