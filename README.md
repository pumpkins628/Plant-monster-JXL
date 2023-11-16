# Plant-monster-JXL
This project utilizes the Feather Huzzah ESP8266 WiFi and Arduino Uno interconnected and other hardware components to create an intelligent watering reminder system for plant owners. Different water threshold values can be set for various plant types, with the code specifying a minimum of 150 and a maximum of 230. When the soil humidity falls below 150, the red LED and buzzer connected to Arduino activate simultaneously, alerting the user to the need for watering. In the range of 150 to 230, the LED, buzzer, and motor remain in a dormant state, providing no cues. However, when the soil humidity exceeds 230, the buzzer emits a frequency distinct from the low humidity alert, the motor engages, lifting a flag bearing the inscription 'Well Done.'

Additionally, the LCD screen displays real-time data on environmental temperature, humidity, and soil moisture, enabling users to promptly perceive changes in the surroundings. This design delivers watering reminders and furnishes users with comprehensive information on the plant's growth environment. Through this smart system, users can conveniently monitor and manage the plant's growth conditions, enhancing the efficiency and convenience of plant care.
## Section one: Required hardware (What I need)
### 1.1 Required components
|Hardware |Description |
| --- | --- |
| ESP8266 | Connect to wifi and publish data which is caught by sensor to MQTT server |
| DHT22 | Sensor for temperature and humidity in air|
| Raspberry Pi | Minicomputer, store and visualise the data in this project|
| resistor | Limit the voltage to tolerant range, build the circuit, protect the whole system |
| red LED | A light indicates the need for water |
| nails*2 | Measure the electrical resistance in the soil to get moisture data|
| Arduino | Connect with ESP8266 to realize serial communication and exchange data |
| LCD | Show more information about the environment  |
| Buzzer | Make some music when watering the plant |
| Engine | Shake the small flag to indicate the plant to get enough water |
## Section two: Work that has been done in workshop (What I learned)
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

## Section three:More functions I added(what I found interesting)

### 3.1 Intelligent prompt watering system

Through serial communication, I successfully connected ESP8266 to Arduino to transmit the three data acquired by Huzzah to Arduino. By expanding the connections on Arduino to include additional components, the overall functionality and enjoyment of the system are enhanced, contributing to an improved quality of life. Specifically, within the entire system, users have the flexibility to customize the desired soil moisture threshold. I've set the soil moisture range in my sample code from 150 to 230. When the soil moisture falls below 150, the red LED and buzzer connected to Arduino activate simultaneously, signaling the need for watering. The LED, buzzer, and motor remain inactive if the soil moisture is between 150 and 230. However, when the soil moisture exceeds 230, the buzzer emits a different frequency, and the motor starts operating, lifting a flag bearing the inscription "Well Done." To enhance the user experience, we've also incorporated an LCD screen to display real-time environmental data.In this way, people who are not plant experts can take better care of their plants and adjust their plant status according to the changes in the environment.

### 3.2 Design process

#### 3.2.1 Establish a serial port connection

In the ESP8266 section, I customized pins 14 and 16 as a software serial interface to transmit the obtained air temperature, humidity, and soil moisture values. Simultaneously, I utilized Arduino's hardware serial interface to receive this information. Throughout this process, it is crucial to ensure that both sections share the same baud rate and establish a common ground when making connections between them. As we cannot directly observe the success of ESP8266 in transmitting information through serial communication, a validation step is implemented in the Arduino's receiving code. This involves printing all obtained information in the serial monitor to check the success of this step. This validation step is essential to ensure the smooth operation of the system.` (See Extea_founction for detailed code) `

![54b3f8894bb9820b8fb5c3923ed1897](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/1810a40c-080f-474d-93cb-3a7a35d4a488)

#### 3.2.2 Implementing functionality using Arduino

First, we need to set up the pins used by the LCD, LED, buzzer, and motor and connect them according to the diagram below. Then, write the logic for the desired functionality .` (See uno_part for detailed code) ` As I couldn't find a motor in the lab, the final product won't showcase the motor and flag functionalities, but you can still refer to the code for their implementation.

![e16ecdd5d9b284fd0097aaae54531db](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/4b6041bb-4109-482c-8238-89cc2cb35a2f)

**It's important to note that the LCD display may exhibit incorrect readings due to unstable wiring or other issues. While ensuring the logical integrity of the code, careful investigation of potential wiring problems is necessary.**

### 3.3 End product

**The soil humidity is 103, below the set minimum threshold. The red LED is lit, and the buzzer is sounding.**

![7d9f04388750740d186b0b238d32e73](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/d750c1d2-4df0-4719-9504-b780e1926609)

**The soil humidity is 167, within the set range, and the components remain inactive.**

![33d3daa1250916ccc1939dea2919426](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/f7776481-15c8-4c8f-aa9f-1c317cbdb7bf)

**The soil humidity is 290, exceeding the maximum threshold. The motor starts, and the buzzer is sounding.**

![f2ad3779c3a37966f49b9b1bf611232](https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/f49af9f6-a486-4786-b9bf-4cec47a0f902)

**We can also use InfluxDB and Grafana to view our historical data. The charts show that the soil moisture has significantly increased twice in the two days of recorded data, corresponding to the two times I watered the plants. Additionally, I have incorporated different display methods in Grafana to present the data more effectively.**

<img width="1280" alt="dc258ae126e0688657e253e86e10cea" src="https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/e45bcfa1-3789-423e-8729-e34220a01aa8">
<img width="1280" alt="23622afcc3c18d226076f21bb0ad679" src="https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/cc27001a-92ba-4fdc-9e0f-328b51756b3a">
<img width="1280" alt="50c6869bea7ff49c2363c214fc3cfdf" src="https://github.com/pumpkins628/Plant-monster-JXL/assets/146323702/d5e536ad-545c-4cfc-b6b5-05b9206f5d9c">

## Section four: Some problems I met (What I struggled but figured out）

**1.During the WiFi connection process, I mistakenly connected to the wrong WiFi network, which resulted in a prolonged inability to connect. I also incorrectly assumed it was a network issue, actually there was issue with the code.**

**2.During the testing of MQTT, I forgot to change the username to my own, which led to me being unable to locate the test data I had uploaded.**

**3.While setting up the Raspberry Pi, I entered incorrect WiFi information, which prevented me from logging in via SSH. With Duncan's assistance, we connected an external monitor, keyboard, and mouse to the Raspberry Pi and made the necessary network adjustments. I also learned that it's crucial to ensure that both the Huzzah and the Raspberry Pi are connected to the same WiFi network for data transfer and subsequent functionality.**

**4.When I was assisting a classmate with the installation of Telegraf, I couldn't find "mqtt_consumer" under "mqtt-data" on the web page. Upon closer inspection, I realized that the username in the code was inconsistent. This taught me the importance of thoroughly reviewing code, including checking for consistency in formatting, both in English and Chinese.**

**5.Throughout the project, I encountered some login issues with Grafana, prompting me to reflash the SD card in the Raspberry Pi. Following the guidance from the workshop, I then reinstalled various configurations.**

**6.I faced some challenges configuring serial communication, leading to the initial transmission of mess data. Through continuous fixes of the code, I successfully figured it out. Therefore, it is essential to verify whether Arduino receives the intended content.**

## Section five：Improvement

**1.The sound of the buzzer is too sharp; it can be replaced with gentle music.**

**2.Once the motor is found, it can be added to the entire system.**

**The development of the Internet of Things makes our lives more convenient and better!!**


