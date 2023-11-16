#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


// LCD setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// LED, Buzzer, and Motor setup
const int ledPin = 8;  //Pin for LED control
const int buzzerPin = 9; //Pin for buzzer control
const int motorPin = 10; // Pin for motor control

// Threshold for soil moisture
const int moistureThresholdLow = 150;  // Low moisture threshold
const int moistureThresholdHigh = 230; // High moisture threshold

// Variables to store sensor data
float temperature, humidity, soilMoisture;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  lcd.begin(16, 2);
  
  Serial.begin(115200); // Set baud rate for SoftwareSerial
}

void loop() {
  // Read data from other device
  if (Serial.available()) {
    String inputString = Serial.readStringUntil('\n');
    if (inputString.startsWith("temp:")) {
      temperature = inputString.substring(6).toFloat();
    }
    else if (inputString.startsWith("humi:")) {
      humidity = inputString.substring(6).toFloat();
    }
    else if (inputString.startsWith("moi:")) {
      soilMoisture = inputString.substring(5).toFloat();
    }
  }

  // Update LCD display
  lcd.setCursor(0, 0);
  delay(1000);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print(" H:");
  lcd.print(humidity, 1);
   lcd.setCursor(0, 1);
   delay(1000);
  lcd.print("Moi:");
  lcd.print(soilMoisture);

  if (soilMoisture < moistureThresholdLow) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); // The frequency of sound produced at low moisture
    digitalWrite(motorPin, LOW); // Flag down
  
  } else if (soilMoisture > moistureThresholdHigh) {
    digitalWrite(ledPin, LOW);
    tone(buzzerPin, 2000); // The frequency of sound produced at high moisture
    digitalWrite(motorPin, HIGH);// Flag up
    delay(1000);
    lcd.setCursor(0, 1);

  } else {
    // In the case of the threshold range, you can choose to perform other operations or stay still
    digitalWrite(ledPin, LOW);//Turn off LED
    noTone(buzzerPin); // Stop buzzer
    digitalWrite(motorPin, LOW); // Stop motor
    lcd.setCursor(0, 1);

  }
}
