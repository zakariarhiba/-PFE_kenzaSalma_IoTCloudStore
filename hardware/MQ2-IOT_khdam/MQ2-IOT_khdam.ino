
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ESP32Servo.h> // Include the ESP32Servo library

const char* ssid = "OPPO Find X5 Lite";
const char* password = "q5jm9h78";
const char* getLedUrlSalon = "https://kenzaiot.000webhostapp.com/phps/get_led_salon.php";
const char*  getLedUrlCusine = "https://kenzaiot.000webhostapp.com/phps/get_led_cuisine.php";

const int ledPinCuisine = 25;  // Replace with the GPIO pin number connected to the LED
const int ledPinSalon = 26; 


int state_ir;


#define IR_Sensor 8
#define DHTPIN 14        // Replace with the GPIO pin number connected to the DHT11
#define DHTTYPE DHT11    // DHT 11
#define SERVO_PIN 2
#define PinMq2 34

DHT dht(DHTPIN, DHTTYPE);
Servo myServo; // Use the ESP32Servo library

void setup() {
  pinMode(ledPinCuisine, OUTPUT);
  pinMode(ledPinSalon, OUTPUT);
  pinMode(PinMq2, INPUT);
  pinMode(IR_Sensor, INPUT_PULLUP);


  myServo.attach(SERVO_PIN);
  myServo.write(0); // Adjust the angle as needed

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

    
    String postUrl = "https://kenzaiot.000webhostapp.com/phps/insert_sensor_data.php?temperature=" + String(temperature) + "&humidity=" + String(humidity)+"&gaz="+getGaz();
    
    HTTPClient http;
    http.begin(postUrl);  // Specify request destination
    int httpCode = http.GET();  // Make the request


    if (httpCode > 0) {  // Check the returning code
        String payload = http.getString();  // Get the request response payload
        Serial.println("Server Response: " + payload);
    } else {
        Serial.println("Error on HTTP request");
    }

    http.end();  // Close connection
  } else {
    Serial.println("WiFi Disconnected");
  }



    // Reading Led Cusine statuts
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(getLedUrlCusine);  // Specify request destination
      int httpCode = http.GET();  // Make the request
  
      if (httpCode > 0) {  // Check the returning code
          String payload = http.getString();  // Get the request response payload
          Serial.println("Server Response: " + payload);
          controlLEDCusine(payload);  // Control LED based on the state received
      } else {
          Serial.println("Error on HTTP request");
      }
      http.end();  // Close connection
    } else {
      Serial.println("WiFi Disconnected");
    }



    // Reading Led Salon statuts
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(getLedUrlSalon);  // Specify request destination
      int httpCode = http.GET();  // Make the request
  
      if (httpCode > 0) {  // Check the returning code
          String payload = http.getString();  // Get the request response payload
          Serial.println("Server Response: " + payload);
          controlLEDSalon(payload);  // Control LED based on the state received
      } else {
          Serial.println("Error on HTTP request");
      }
  
      http.end();  // Close connection
    } else {
      Serial.println("WiFi Disconnected");
    }


    // verifying the ir sensor state
    state_ir  = digitalRead(IR_Sensor);

    if(state_ir == HIGH){
      myServo.write(90); // Adjust the angle as needed
      delay(2000); // Wait for a second
      myServo.write(0); // Adjust the angle as needed
    }

  
  delay(5000);  // Wait for 5 seconds
}

void controlLEDCusine(String state) {
  if (state == "ON") {
    digitalWrite(ledPinCuisine, HIGH);  // Turn the LED on
    Serial.println("LED turned ON");
  } else if (state == "OFF") {
    digitalWrite(ledPinCuisine, LOW);  // Turn the LED off
    Serial.println("LED turned OFF");
  }
}


void controlLEDSalon(String state) {
  if (state == "ON") {
    digitalWrite(ledPinSalon, HIGH);  // Turn the LED on
    Serial.println("LED turned ON");
  } else if (state == "OFF") {
    digitalWrite(ledPinSalon, LOW);  // Turn the LED off
    Serial.println("LED turned OFF");
  }
}


String getGaz(){
   int gaz_val = analogRead(PinMq2);
   String gaz = String(gaz_val);
   return gaz;
}
