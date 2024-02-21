#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const char* ssid = "OPPO Find X5 Lite";
const char* password = "q5jm9h78";

#define DHTPIN 14        // Replace with the GPIO pin number connected to the DHT11
#define DHTTYPE DHT11    // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Read DHT11 sensor data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    String postUrl = "https://iotsystemest.000webhostapp.com/insert_sensor_data.php?temperature=" + String(temperature) + "&humidity=" + String(humidity);

    HTTPClient http;
    http.begin(postUrl);  // Specify request destination
    int httpCode = http.GET();  // Make the request

    if (httpCode > 0) {  // Check the returning code
        String payload = http.getString();  // Get the request response payload
        Serial.println("Temperature: " + String(temperature) + "C, Humidity: " + String(humidity) + "%");
    } else {
        Serial.println("Error on HTTP request");
    }

    http.end();  // Close connection
  } else {
    Serial.println("WiFi Disconnected");
  }
  
  delay(5000);  // Wait for 5 seconds
}
