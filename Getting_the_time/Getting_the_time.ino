#include <ESP8266WiFi.h> //The purpose of connecting to WiFi is the same as the previous operation. If there is no corresponding library, download it from the resource library first. What needs to be added here is ezTime time library
#include <ezTime.h>

const char* ssid     = "CE-Hub-Student"; //Connect to wifi in the lab
const char* password = "casa-ce-gagarin-public-service";

Timezone GB;//Create an object for processing time
const char* host = "wifitest.adafruit.com";

void setup() {  //The following operations to connect to WiFi are the same as the previous procedure
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  waitForSync();//Wait for time synchronization to ensure that accurate time information is used during program running

  Serial.println("UTC: " + UTC.dateTime());

  GB.setLocation("Europe/London");//This action sets the time zone, which in this case is London
  Serial.println("London time: " + GB.dateTime());  //Output London time
}

int value = 0;

void loop() {//This function performs operations in the format of "H:i:s" per second, and we can see the results on the serial monitor
 delay(1000);
  Serial.println(GB.dateTime("H:i:s"));
}