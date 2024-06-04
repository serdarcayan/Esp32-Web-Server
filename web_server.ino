#include <WiFi.h>
#include <WebServer.h>
#include "page.h"

const char* ssid = "";
const char* password = "";

WebServer server(80);

const int redPin = 15;   
const int greenPin = 4;  
const int bluePin = 5;   

void handleRoot() {
  server.send(200, "text/html", webpageCode);
}

void handleSetRGB() {
  if (server.args() == 3) {
    int redValue = server.arg(0).toInt();
    int greenValue = server.arg(1).toInt();
    int blueValue = server.arg(2).toInt();

    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);

    server.send(200, "text/plain", "RGB set");
  } else {
    server.send(400, "text/plain", "Bad request");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("WiFi connected.");
  Serial.print("IP Adress: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/setRGB", handleSetRGB); 
  server.begin();
  Serial.println("HTTP server has been stared.");
}

void loop() {
  server.handleClient();
}
