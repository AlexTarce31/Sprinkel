#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

//------- WI-FI details ----------//
char ssid[] = "AlexS23"; //SSID here
char pass[] = "Mata1234@"; // Passowrd here
unsigned long Channel_ID =  2187833; // Your Channel ID
const char * myWriteAPIKey = "D7TXSU0U7871RTE9"; //Your write API key
//-------------------------------------------//

const int Field_Number_1 = 1;
const int Field_Number_2 = 2;
const int Field_Number_3 = 3;
String value = "";
int value_1 = 0, value_2 = 0, value_3 = 0;
int x, y;
WiFiClient  client;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  WiFi.begin(ssid, pass);
  delay(5000);
}

void loop()
{
    Serial.println("Conectat");
    value = Serial.readString();
    if (value[0] == '*')
    {
      if (value[9] == '#')
      {
        value_1 = ((value[1] - 0x30) * 10 + (value[2] - 0x30));
        value_2 = ((value[3] - 0x30) * 10 + (value[4] - 0x30));
        value_3 = ((value[5] - 0x30) * 1000 + (value[6] - 0x30) * 100 + (value[7] - 0x30) * 10 + (value[8] - 0x30));
      }

      if (value[8] == '#')
      {
        value_1 = ((value[1] - 0x30) * 10 + (value[2] - 0x30));
        value_2 = ((value[3] - 0x30) * 10 + (value[4] - 0x30));
        value_3 = ((value[5] - 0x30) * 100 + (value[6] - 0x30) * 10 + (value[7] - 0x30));
      }

      if (value[7] == '#')
      {
        value_1 = ((value[1] - 0x30) * 10 + (value[2] - 0x30));
        value_2 = ((value[3] - 0x30) * 10 + (value[4] - 0x30));
        value_3 = ((value[5] - 0x30) * 10 + (value[6] - 0x30));
      }

      if (value[6] == '#')
      {
        value_1 = ((value[1] - 0x30) * 10 + (value[2] - 0x30));
        value_2 = ((value[3] - 0x30) * 10 + (value[4] - 0x30));
        value_3 = ((value[5] - 0x30));
      }

      if (value[5] == '#')
      {
        value_1 = ((value[1] - 0x30) * 10 + (value[2] - 0x30));
        value_2 = ((value[3] - 0x30) * 10 + (value[4] - 0x30));
        value_3 = 1000;
      }
    }
    
  upload();
  delay(100);
}

void upload()
{
  ThingSpeak.writeField(Channel_ID, Field_Number_1, value_1, myWriteAPIKey);
  delay(10000);
  ThingSpeak.writeField(Channel_ID, Field_Number_2, value_2, myWriteAPIKey);
  delay(10000);
  ThingSpeak.writeField(Channel_ID, Field_Number_3, value_3, myWriteAPIKey);
  delay(10000);
  value = "";
}
