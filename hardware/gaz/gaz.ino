#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

const int Sensor_input = 12;

void setup() {
  Serial.begin(115200);
  pinMode(Sensor_input, INPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int sensor_Aout = analogRead(Sensor_input);

    HTTPClient http;
    String serverPath = "https://iotsystemest.000webhostapp.com/insert_sensor_data.php?value=" + String(sensor_Aout);
    
    http.begin(serverPath);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }

  delay(4000); // Wait for 1 minute
}
