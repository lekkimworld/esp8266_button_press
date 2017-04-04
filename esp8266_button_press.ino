
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Radisson_Guest";
const char* password = "";
const int httpPort = 80;
const char* host = "10.43.1.252";
const int pin = 2;
int prevState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(pin, INPUT);
  Serial.println("Started....");
  Serial.print("Mac address: "); Serial.println(WiFi.macAddress());
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
}

void loop() {
  int state = digitalRead(pin);
  if (state != prevState) {
    // create connection
    WiFiClient client;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
    
    // We now create a URI for the request
    String url = (state == HIGH) ? "/on" : "/off";
    Serial.print("Requesting URL: ");
    Serial.println(url);
    
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
      "Host: " + host + "\r\n" + 
      "Connection: close\r\n\r\n");
    delay(10);

    // save state
    prevState = state;
  }
  delay(200);
}
