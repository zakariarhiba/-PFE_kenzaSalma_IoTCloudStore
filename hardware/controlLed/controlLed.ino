#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "OPPO Find X5 Lite";
const char* password = "q5jm9h78";
const char* getLedUrl = "https://kenzaiot.000webhostapp.com/get_led.php";

const int ledPin = 25;  // Replace with the GPIO pin number connected to the LED

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  
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
    HTTPClient http;
    http.begin(getLedUrl);  // Specify request destination
    int httpCode = http.GET();  // Make the request

    if (httpCode > 0) {  // Check the returning code
        String payload = http.getString();  // Get the request response payload
        Serial.println("Server Response: " + payload);
        controlLED(payload);  // Control LED based on the state received
    } else {
        Serial.println("Error on HTTP request");
    }

    http.end();  // Close connection
  } else {
    Serial.println("WiFi Disconnected");
  }
  
  delay(5000);  // Wait for 5 seconds
}

void controlLED(String state) {
  if (state == "ON") {
    digitalWrite(ledPin, HIGH);  // Turn the LED on
    Serial.println("LED turned ON");
  } else if (state == "OFF") {
    digitalWrite(ledPin, LOW);  // Turn the LED off
    Serial.println("LED turned OFF");
  }
}
