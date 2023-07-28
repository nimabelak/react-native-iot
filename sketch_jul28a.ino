#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char* ssid = "MobinNet79E3";
const char* password = "EFFE79E3";

// LED Pin
const int ledPin = D1;

// Web Server on port 80
ESP8266WebServer server(80);

void setup() {
  // Initialize LED pin
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Start the server
  server.on("/onoff", handleLEDOnOff);
  server.begin();
  Serial.println("Server started");
}

void handleLEDOnOff() {
  if (server.method() == HTTP_POST) {
    String requestBody = server.arg("plain");
    if (requestBody.indexOf("isLedOn") != -1) {
      bool isLedOn = requestBody.indexOf("true") != -1;
      digitalWrite(ledPin, isLedOn ? HIGH : LOW);
      server.send(200, "text/plain", isLedOn ? "LED ON" : "LED OFF");
    }
  }
}

void loop() {
  server.handleClient();
}
