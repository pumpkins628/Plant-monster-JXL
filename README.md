# Plant-monster-JXL
## Section one: Required hardware
### 1.1 Hardware already in use
|Hardware |Description |
| --- | --- |
| ESP8266 | Connect to wifi and publish data which is caught by sensor to MQTT server |
| DHT22 | Sensor for temperature and humidity in air|
| Raspberry Pi | Minicomputer, store and visualise the data in this project|
| resistor | Limit the voltage to tolerant range, build the circuit, protect the whole system |
| LED | A light indicates the need for water |
| nails*2 | Measure the electrical resistance in the soil to get moisture data|
### 1.2 Hardware plan to use
|Hardware |Description |
| --- | --- |
| Arduino | Connect with ESP8266 to realize serial communication and exchange data |
| LCD | Show more information about the environment  |
| Buzzer | Make some music when watering the plant |
| LED*n | Decorate the whole system |
| Engine | Shake the small flag to indicate the plant to get enough water |
## Section two: Work that has been done
### 2.1 Connecting WiFi
