#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>

/* Network settings */
const char* ssid = "Angel"; // SSID - your WiFi"s name
const char* password = "12345678"; // Password

const int REDPIN = 0;  // D3 GPIO0
const int GREENPIN = 2;  // D2 GPIO2
const int BLUEPIN = 4;  // D4 GPIO4

WiFiServer server(80);

#define FADESPEED 5     // make this higher to slow down

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  // Connect to WiFi network
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

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address on serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  //  int r, g, b;
  //
  //  for (g = 0; g < 256; g++) {
  //    analogWrite(GREENPIN, g);
  //    delay(FADESPEED);
  //  }
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request


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

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1 align=center>Lights controlled over WiFi</h1><br><br>");
  client.print("Lights are changing= ");

  client.println("<br><br>");
  client.println("<a href=\"/red\"\"><button> turn lights red </button></a>");
  client.println("<a href=\"/blue\"\"><button>turn lights blue </button></a><br />");
  client.println("<a href=\"/green\"\"><button>turn lights green </button></a><br />");
  client.println("<a href=\"/off\"\"><button>turn lights off </button></a><br />");
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");


}
