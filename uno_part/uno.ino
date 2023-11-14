#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// LCD setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// LED, Buzzer, and Motor setup
const int ledPin = 8;
const int buzzerPin = 9;
const int motorPin = 10; // Example pin for motor control

// Threshold for soil moisture
const int moistureThresholdLow = 150;  // 低湿度阈值
const int moistureThresholdHigh = 200; // 高湿度阈值

// SoftwareSerial for communication
//SoftwareSerial mySerial(2, 3); // RX, TX

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
    tone(buzzerPin, 1000); // 低湿度时发出的声音频率
    digitalWrite(motorPin, LOW); // 电机控制（flag down）
  
  } else if (soilMoisture > moistureThresholdHigh) {
    digitalWrite(ledPin, LOW);
    tone(buzzerPin, 2000); // 高湿度时发出的声音频率
    digitalWrite(motorPin, HIGH); // 电机控制（flag up）
    lcd.setCursor(0, 1);

  } else {
    // 在阈值范围内的情况下，可以选择执行其他操作或保持静止
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin); // 停止蜂鸣器声音
    digitalWrite(motorPin, LOW); // 电机保持静止
    lcd.setCursor(0, 1);

  }
}
