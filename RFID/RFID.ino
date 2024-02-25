#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h> // Include the ESP32Servo library

#define SS_PIN  5  // ESP32 pin GPIO5 
#define RST_PIN 16 // ESP32 pin GPIO27 
#define LED_PIN 12 // ESP32 built-in LED pin
#define SERVO_PIN 2 // Choose an appropriate pin for the servo motor

MFRC522 rfid(SS_PIN, RST_PIN);  
Servo myServo; // Use the ESP32Servo library

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
  myServo.attach(SERVO_PIN); // Attach the servo motor to the specified pin

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been read
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));

      // Print UID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      // Turn on the LED
      digitalWrite(LED_PIN, HIGH);

      // Move the servo motor
      myServo.write(90); // Adjust the angle as needed
      delay(1000); // Wait for a second

      // Halt and stop crypto
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();

      // Turn off the LED
      digitalWrite(LED_PIN, LOW);

      // Move the servo motor back to its initial position
      myServo.write(0); // Adjust the angle as needed
      delay(1000); // Wait for a second
    }
  }
}
