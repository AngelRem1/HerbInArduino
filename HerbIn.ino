#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Create a main page
//#include "mainpage.h"

/* Network settings */
const char* ssid = "Angel"; // SSID - your WiFi"s name 
const char* password = "12345678"; // Password 
const char* device_name = "led"; // you can access controller by http://led.local/


//Change the IP address to reflect your Router subnet, and make sure that there is no devices in the same IP address.
IPAddress ip(192,168,1,111);  // static IP adress of device 
IPAddress gateway(192,168,1,1); // Gateway
IPAddress subnet(255,255,255,0); // Network mask

const int REDPIN = 0;  // D3 GPIO0
const int GREENPIN = 2;  // D2 GPIO2
const int BLUEPIN = 4;  // D4 GPIO4

ESP8266WebServer server(80);

#define FADESPEED 5     // make this higher to slow down
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}
//
//void setup(void) {
// delay(1000);
// /* Begin some (un)important things */
//   Serial.begin(115200);
//   WiFi.begin(ssid, password);
//   WiFi.config(ip, gateway, subnet);
//   Serial.println("");
//
////   stuff for the pins 
//  pinMode(redLED, INPUT);
//  pinMode(greenLED, INPUT);
//  pinMode(blueLED, INPUT);
//
//  green();
//    
////   server.on("/", []() {
////     server.send(200, "text/html", "<p> Does this work </p>");
////     Serial.println("Loaded main page");
////     Serial.print("Pressed: ");
////     Serial.println("on");
////   });
//
////Creating routes for turning on and off
////   server.on("/red", []() {
////     server.send(200, "text/html","<p> Does this work1 </p>");
////     red();
////     Serial.print("Pressed: ");
////     Serial.println("red");
////     delay(1000);
////   });
//
////   server.on("/blue", []() {
////     server.send(200, "text/html","<p> Does this work2 </p>");
////     blue();
////     Serial.print("Pressed: ");
////     Serial.println("blue");
////     delay(1000);
////   });
////   server.on("/green", []() {
////     server.send(200, "text/html","<p> Does this work3 </p>");
////     green();
////     Serial.print("Pressed: ");
////     Serial.println("green");
////     delay(1000);
////   });
//
//  
//}
//
//void green() {
//  digitalWrite(greenLED, HIGH);
//}
//
//void red() {
//  digitalWrite(redLED, HIGH);
//}
//
//void blue() {
//  digitalWrite(blueLED, HIGH);
//}
void loop() {
  int r, g, b;
 
  // fade from blue to violet
//  for (r = 0; r < 256; r++) { 
//    analogWrite(REDPIN, r);
//    delay(FADESPEED);
//  } 
  // fade from violet to red
//  for (b = 255; b > 0; b--) { 
//    analogWrite(BLUEPIN, b);
//    delay(FADESPEED);
//  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  } 
  // fade from yellow to green
//  for (r = 255; r > 0; r--) { 
//    analogWrite(REDPIN, r);
//    delay(FADESPEED);
//  } 
  // fade from green to teal
//  for (b = 0; b < 256; b++) { 
//    analogWrite(BLUEPIN, b);
//    delay(FADESPEED);
//  } 
  // fade from teal to blue
//  for (g = 255; g > 0; g--) { 
//    analogWrite(GREENPIN, g);
//    delay(FADESPEED);
//  } 
}
