/*
 * This ESP client connects to the Oracle server.
 * This is a template that allows for the specific ESP to send a command to the server
 * The command is preceded by the ESP name signifying which device the message
 * is received from.
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

const char* ID = "";
const char* PASS = "";
const String DEV_ID = "TestESP";

#ifndef STASSID
#define STASSID ID
#define STAPSK PASS
#endif

const String host = "";
const uint16_t port = ;

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ID,PASS);

  Serial.println();
  Serial.print("Checking WiFi Connection");
  while(WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi connected");

}

void loop() {
  Serial.println("Connecting to host: ");
  Serial.print(host);
  Serial.print(":");
  Serial.print(port);

  WiFiClient client;
  if(!client.connect(host,port))
  {
    Serial.println("Connection Failed");
    delay(3000);
    return;
  }
  //Put code here to determine message sent to server
  //This code simply sends the test message "Found"
  //along with the name of the device.
  client.println(DEV_ID + "Found");
  Serial.println("Code Sent, resending in 5 seconds");
  client.stop();
  delay(5000);
}
