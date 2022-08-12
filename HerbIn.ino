#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>

/* Network settings */
const char* ssid = "Angel"; // SSID - your WiFi"s name
const char* password = "12345678"; // Password

/* pins for the led */
const int REDPIN = 2 ;  // D3 GPIO0
const int GREENPIN = 0;  // D2 GPIO2
const int BLUEPIN = 4;  // D4 GPIO4

/* pins for the 2 channel relay using D5 and D6*/
const int IN1 = 12; //D6 GPIO12
const int IN2 = 13; //D7 GPIO13

/* pins for analog signal for both moisture sensor */
const int PIN1 = A0;

/* for the multiplexor */
const int MULTIPIN = 14; /* selector pin for the multiplexor */

/* variable to store the value of the moisture sensor */
float VALUE = 0;

WiFiServer server(80);

#define FADESPEED 5    /* increase to slow down */


/* Functions to turn on/off pump */
void turnOnPump1() {
  digitalWrite(IN1, LOW);
  delay(50);
  turnOffPump1();

}

void turnOnPump2() {
  digitalWrite(IN2, LOW);
  delay(50);
  turnOffPump2();

}

void turnOffPump1() {
  digitalWrite(IN1, HIGH);
}
void turnOffPump2() {
  digitalWrite(IN2, HIGH);
}

void setup() {
  Serial.begin(115200);
  delay(10);


  /* setting port input and output function for arduino (for LED) */
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);

  /* setting ports input and out function for arduino (for pump and moisture sensor) */
  pinMode(IN1, OUTPUT); //Pump 1
  pinMode(IN2, OUTPUT);  //Pump 2

  pinMode(PIN1, INPUT); //Moisture sensor

  /* Turning off the relay */
  Serial.println("Turning off relay");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);

  /* Connect to WiFi network */
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  /* Start the server */
  server.begin();
  Serial.println("Server started");

  /* Print the IP address on serial monitor */
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    /* URL IP to be typed in mobile/desktop browser */
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  /* Displaying the moisture level */

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  /* Wait until the client sends some data */
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  /* Read the first line of the request */
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();


  /* Match the request */
  if (request.indexOf("/red") != -1)  {
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN, 255);
    delay(FADESPEED);

  }

  if (request.indexOf("/blue") != -1)  {

    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 255);
    delay(FADESPEED);
  }

  if (request.indexOf("/green") != -1)  {
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 255);
    delay(FADESPEED);
  }

  if (request.indexOf("/off") != -1)  {
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
    delay(FADESPEED);
  }

  if (request.indexOf("/pumpOn1") != -1)  {
    turnOnPump1();
  }

  if (request.indexOf("/pumpOn2") != -1)  {
    turnOnPump2();
  }

  if (request.indexOf("/checkMoisture1") != -1)  {

    digitalWrite(MULTIPIN, HIGH);
    Serial.println();
    Serial.println();
    Serial.println("Moisture level #1:");
    VALUE = analogRead(PIN1);
    client.println(VALUE);
    Serial.println(VALUE);
    Serial.println();
  }
  if (request.indexOf("/checkMoisture2") != -1)  {
    digitalWrite(MULTIPIN, LOW);
    Serial.println();
    Serial.println();
    Serial.println("Moisture level #2:");
    VALUE = analogRead(PIN1);
    client.println(VALUE);
    Serial.println(VALUE);
    Serial.println();
  }





  /* Return the response */
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); /* do not forget this one */
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1 align=center>Lights controlled over WiFi</h1><br><br>");
  client.print("Lights are changing= ");

  client.println("<br><br>");
  client.println("<a href=\"/red\"\"><button> turn lights red </button></a>");
  client.println("<a href=\"/blue\"\"><button>turn lights blue </button></a><br />");
  client.println("<a href=\"/green\"\"><button>turn lights green </button></a><br />");
  client.println("<a href=\"/off\"\"><button>turn lights off </button></a><br />");
  client.println("<a href=\"/pumpOn1\"\"><button>turn on pump </button></a><br />");
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");


}
