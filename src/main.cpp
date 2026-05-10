#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// WIFI
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// FLASK SERVER
const char* server = "http://YOUR_PC_IP:5000/data";

// PINS
#define PIR 27
#define IR 26
#define RELAY 23
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// POWER SAVING
unsigned long lastMotionTime = 0;
const unsigned long timeout = 300000; // 5 mins

void setup() {

  Serial.begin(115200);

  pinMode(PIR, INPUT);
  pinMode(IR, INPUT);
  pinMode(RELAY, OUTPUT);

  digitalWrite(RELAY, LOW);

  dht.begin();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");
}

void loop() {

  // READ SENSORS
  int pir = digitalRead(PIR);
  int ir = digitalRead(IR);

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // PRINT
  Serial.print("PIR: ");
  Serial.println(pir);

  Serial.print("IR: ");
  Serial.println(ir);

  Serial.print("TEMP: ");
  Serial.println(temp);

  Serial.print("HUM: ");
  Serial.println(hum);

  // AUTO LIGHT CONTROL
  if (pir == 1) {

    digitalWrite(RELAY, HIGH);

    lastMotionTime = millis();

    Serial.println("Room Occupied → Light ON");
  }

  // POWER SAVING
  if (millis() - lastMotionTime > timeout) {

    digitalWrite(RELAY, LOW);

    Serial.println("No motion for 5 mins → Light OFF");
  }

  // INTRUSION ALERT
  int hour = 23; // Example night time

  if (hour >= 22 && pir == 1) {

    Serial.println("⚠️ INTRUSION ALERT!");
  }

  // SEND DATA TO FLASK
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(server);

    http.addHeader("Content-Type", "application/json");

    String json = "{";

    json += "\"pir\":" + String(pir) + ",";
    json += "\"ir\":" + String(ir) + ",";
    json += "\"temp\":" + String(temp) + ",";
    json += "\"hum\":" + String(hum);

    json += "}";

    int code = http.POST(json);

    Serial.print("Response: ");
    Serial.println(code);

    http.end();
  }

  delay(3000);
}
