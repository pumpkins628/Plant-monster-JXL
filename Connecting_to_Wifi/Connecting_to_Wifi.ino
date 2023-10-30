#include <ESP8266WiFi.h> //If we don't have the library beforehand, we need to download it in the repository

const char* ssid     = "CE-Hub-Student";  //If I try to connect this Wi-Fi, it works
const char* password = "casa-ce-gagarin-public-service";
const char* host = "wifitest.adafruit.com";

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //Here you start connecting to the specified Wi-Fi network
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); //Use"." to display the progress of the Wi-Fi connection, which can be seen in the monitor
  }

  Serial.println("");
  Serial.println("WiFi connected");  //Print this sentence after successful connection
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
int value = 0;
void loop() {
  delay(5000);

  Serial.println("-------------------------------"); //A separator line is used to indicate that the connection progress is complete and the following Wi-Fi information is displayed
  Serial.print("Connecting to ");
  Serial.println(host); //Output the name of the host you are connecting to

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");//The connection failed, and an error message was displayed
    return;
  }
  // We now create a URI for the request
  String url = "/data/index.html";
  Serial.print("Requesting URL: ");
  Serial.println(host + url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  delay(500); //The delay here is to ensure that data reception is complete
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line); //Each line of the response is printed here
  }

  Serial.println();
  Serial.println("closing connection");
}
