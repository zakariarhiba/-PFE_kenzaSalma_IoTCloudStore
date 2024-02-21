#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const char* ssid = "OPPO Find X5 Lite";
const char* password = "q5jm9h78";
const char* getLedUrl = "https://iotsystemest.000webhostapp.com/get_led.php";

const int ledPin = 25;  // Replace with the GPIO pin number connected to the LED

#define DHTPIN 14        // Replace with the GPIO pin number connected to the DHT11
#define DHTTYPE DHT11    // DHT 11

#define PinMq2 34

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(PinMq2, INPUT);
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
  
  // Sending temperature and humidty values
  if(WiFi.status() == WL_CONNECTED) {
    // Read DHT11 sensor data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int gaz_val = analogRead(PinMq2);

    
    String postUrl = "https://iotsystemest.000webhostapp.com/insert_sensor_data.php?temperature=" + String(temperature) + "&humidity=" + String(humidity)+"&gaz="+String(gaz_val);
    
    HTTPClient http;
    http.begin(postUrl);  // Specify request destination
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



  // Reading Led statuts
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
