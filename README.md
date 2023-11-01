# Plant-monster-JXL
## Section one: Required hardware (What I need)
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
## Section two: Work that has been done (What I learned)
### 2.1 Connecting WiFi
Following the workshop's guidance, we first completed the operation of connecting the ESP8266 development board to the specified Wi-Fi network. This process also includes connecting to a designated host, sending HTTP GET requests, and receiving and printing responses from the server, among other crucial steps. To enhance the visual feedback during this process, we added some output information, such as using a period "." to indicate waiting states during the connection.  ` （See Connecting_to_Wifi for detailed code) ` 

![3b7ed8257e656a6ef6a765c2bf7a425](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/d6a28b98-73ff-480b-8047-b572e57a523c)

### 2.2 Time Synchronization
After connecting to Wi-Fi, it's essential to synchronize the time. After downloading the ezTime library, we created an object for time handling. Once time synchronization is achieved, we can observe real-time updates of the London time zone, displayed in the format (H:i:s), in the serial monitor every second.  ` （See Getting_the_time for detailed code) ` 

![cf651904c38dc25b86802ae8908f081](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/14d62aa8-29b7-41be-89ce-f981cfec6c4d)

### 2.3 Sending Data to the MQTT Server
After successfully configuring the WiFi connection and synchronizing the time, we attempt to send information to the MQTT server. It's worth noting that we need to download the PubSubClient library in advance to handle MQTT connections. In MQTT, we subscribe to the inTopic and control the LED's on/off state by sending messages. ` （See 10.23 testMQTT for detailed code)  ` 

**If we send 1 to inTopic, the LED will turn on.**

![b36a4f7a0f7fe4f639318ad937f0305](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/7c0e31fb-c8ce-499e-856f-7a42cbc0f16c)

**If we send 0 to inTopic, the LED will turn off.**

![f7095b91ad4c99c42d0cc47b39cd1ff](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/43999bf3-842d-4a87-a61a-9caffa99c7f9)

### 2.4 Assemble the Soil Sensor and Send Data to MQTT
After soldering the entire soil sensor system, we will apply the knowledge we've learned to capture moisture, environmental humidity, and temperature data, and send them to MQTT. Each of us uses our student ID as a unique identifier. To record data using the DHT22 sensor, we'll also need to download the corresponding library files. In the end, we can access these three sets of data in real-time via MQTT. If you want a more visual representation of data trends, you can open charts  ` (See 10.25 Soil data for detailed code) ` . Additionally, we've created a simple webpage to display our data, including temperature, humidity, time, and more. With each update, we get the latest data  ` (See Soil_data for detailed code) ` .

![da9b0a60b8aa23bd84ef72ccafd6d6e](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/5f9f50b9-a70a-459b-a0b4-89f2653cdea7)

![6c41b741aec0eec1e9ea579bf1c79ef](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/9aadfed0-86dc-44ec-8848-eb057db6e2c0)


### 2.5 Setting up the Raspberry Pi for Further Data Storage and Display
Before using the Raspberry Pi for data storage and display, some preliminary preparations are required. This includes setting up basic information, Influx, Telegraf, and Grafana. During this process, I used PuTTY to perform login and configuration operations. In the end, we can obtain data visualizations as follows. You can see that the data trends are the same on both web pages, which demonstrates that we have visualized the data using different methods.

![58a5ebf006ea87c56e217f133ad3143](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/0d1568f2-2069-4623-85a7-a0b2540426c2)
## Section three: Some problems (What I struggled but figured out）
**1.During the WiFi connection process, I mistakenly connected to the wrong WiFi network, which resulted in a prolonged inability to connect. I also incorrectly assumed it was a network issue, actually there was issue with the code.**

**2.During the testing of MQTT, I forgot to change the username to my own, which led to me being unable to locate the test data I had uploaded.**

**3.While setting up the Raspberry Pi, I entered incorrect WiFi information, which prevented me from logging in via SSH. With Duncan's assistance, we connected an external monitor, keyboard, and mouse to the Raspberry Pi and made the necessary network adjustments. I also learned that it's crucial to ensure that both the Huzzah and the Raspberry Pi are connected to the same WiFi network for data transfer and subsequent functionality.**

**4.When I was assisting a classmate with the installation of Telegraf, I couldn't find "mqtt_consumer" under "mqtt-data" on the web page. Upon closer inspection, I realized that the username in the code was inconsistent. This taught me the importance of thoroughly reviewing code, including checking for consistency in formatting, both in English and Chinese.**

## Section four：Future plan

**Currently, I have made some simple improvements to the ESP8266, adding an output port and connecting an LED. The purpose of this enhancement is to illuminate the LED when the soil moisture falls below a specified value, serving as a reminder to water the plants. ` （See Soil_data for detailed code)  ` In the future, I plan to connect an Arduino to the ESP8266, enabling data exchange between them through serial communication. I also intend to further expand the hardware setup by incorporating additional components like a buzzer, LCD screen, motor, and more. By developing specific code, I aim to achieve the following functionalities: when the plants require watering, a specific melody will play, and the LED will flash. When we adequately water the plants, a different melody will play, and a motor will raise a small flag to indicate sufficient water supply. Furthermore, an LCD screen will provide real-time display of environmental data and other information.**
![edb95318e1cd69bc1d8c0c47bbd17e2](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/55c09a50-550c-4b32-bfa9-e4a392f8d0d9)
