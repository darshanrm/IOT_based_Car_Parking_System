#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "secrets.h"

char* apiWritekey = "UA06XRYTUU5WYVW4"; // replace with your THINGSPEAK WRITEAPI key here
 char* ssid = "Marathe1"; // your wifi SSID name
 char* password = "coolspot403" ;// wifi pasword
 char* server = "api.thingspeak.com";
unsigned long counterChannelNumber = SECRET_CH_ID_COUNTER;
char * myCounterReadAPIKey = SECRET_READ_APIKEY_COUNTER;
float temp1,temp2,temp3,temp4;
int keyIndex = 0;            // your network key Index number (needed only for WEP)
unsigned int counterFieldNumber1 = 2;
unsigned int counterFieldNumber2 = 4;
unsigned int counterFieldNumber3 = 6;
unsigned int counterFieldNumber4 = 8;
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID_COUNTER;
void setup() {
   Serial.begin(115200);  // Initialize serial

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {


   // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, password);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  long count1 = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber1, myCounterReadAPIKey);  
  long count2 = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber2, myCounterReadAPIKey);  
  long count3 = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber3, myCounterReadAPIKey);  
  long count4 = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber4, myCounterReadAPIKey);  
  
  if(count1 == 0.0){
  temp1 = 0.0;
}

else{
  temp1 = digitalRead(D5);
}
if(count2 == 0.0){
  temp2 = 0.0;
}

else{
  temp2 = digitalRead(D6);
}
if(count3 == 0.0){
  temp3 = 0.0;
}

else{
  temp3 = digitalRead(D7);
}
if(count4 == 0.0){
  temp4 = 0.0;
}

else{
  temp4 = digitalRead(D8);
}

  // set the fields with the values
  ThingSpeak.setField(1, temp1);
  ThingSpeak.setField(3, temp2);
  ThingSpeak.setField(5, temp3);
  ThingSpeak.setField(7, temp4);

  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, apiWritekey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  
  delay(15000); // Wait 20 seconds to update the channel again
}
