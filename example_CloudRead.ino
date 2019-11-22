#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Servo.h>


//----------------  Fill in your credentails   ---------------------
char ssid[] = "Hogwarts_WiFi";     // your network SSID (name) 
char pass[] = "JKRowling"; // your network password
//------------------------------------------------------------------

Servo myservo;
WiFiClient  client;
int led1pin=4
int led2pin=5
int led3pin=6
int tempinputpin=A0

unsigned long CcodeChannelNumber = 917355;
unsigned int  CcFieldNumber = 1;
unsigned long statusChannelNumber = 917359;
unsigned int  statusled1FieldNumber = 1;
unsigned int  statusled2FieldNumber = 2;
unsigned int  statusled3FieldNumber = 3;
unsigned int  statusfanFieldNumber = 4;
unsigned int  statusautoled1FieldNumber = 5;
unsigned int  statusautoled2FieldNumber = 6;
unsigned int  statusautoled3FieldNumber = 7;
unsigned int  statusautofanFieldNumber = 8;
unsigned long tempChannelNumber = 917357;
unsigned int  tempFieldNumber = 1;
unsigned long ldrChannelNumber = 917360;
unsigned int  ldrFieldNumber = 1;

const char* readccAPIKey = "4QWRT1OID7P3AOH6";
const char* writeccAPIKey = "U6DEUI2SRWRL9WHW";
const char* readstatusAPIKey = "CU4W1P240POXKOQP";
const char* writestatusAPIKey = "D0NHX0U06GF6S07Y";
const char* readtempAPIKey = "5DN1YXKWR7WSVZCR";
const char* writetempAPIKey = "OKVY8C07ULV7952P";
const char* readldrAPIKey = "U141VNK3E5WV5U2Z";
const char* writeldrAPIKey = "YDPG4M2LWQ56K70C";

void setup() 
{
 // Initialize serial and wait for port to open:
 // while (!Serial) {
 // wait for serial port to connect. Needed for native USB port only
 // }
 myservo.attach( 9 );
 Serial.begin(115200);
 WiFi.mode(WIFI_STA); 
 WiFi.begin(ssid, pass);
 if(WiFi.status() != WL_CONNECTED)
 {
   Serial.print("Attempting to connect to SSID: ");
   Serial.println(ssid);
   while(WiFi.status() != WL_CONNECTED)
   {
     Serial.print(".");
     delay(500);     
   } 
   Serial.println("\nConnected");
 } 
 ThingSpeak.begin(client);
 
}

void loop() {

 int constatusCode1 = 0;    //is checked after reading from cloud 
 int constatusCode2=0;      //is checked after writing to cloud
 // Read in field 4 of the public channel recording the temperature
int Controlcode = ThingSpeak.readIntField(CcodeChannelNumber,CcFieldNumber,readccAPIKey);
  
//String temperatureInF = ThingSpeak.readStringField(weatherStationChannelNumber,temperatureFieldNumber,readAPIKey);  

constatusCode1 = ThingSpeak.getLastReadStatus();

 // Check the status of the read operation to see if it was successful
 
if(constatusCode1 == 200)
{
    switch(Controlcode)
     {
      case 101:
               constatuscode2=ThingSpeak.writeField( statusChannelNumber,statusled1FieldNumber,1,writestatusAPIKey);
               if(constatuscode2!=200)
                  {
               Serial.println("Error updating status to cloud. Error code: ");
               Serial.print(constatuscode2);
                   }
               else
                 {
                    digitalWrite(led1pin,HIGH);
                    Serial.println("living room light is on");
                  }
      case 102: 
               constatuscode2=ThingSpeak.writeField( statusChannelNumber,statusled2FieldNumber,1,writestatusAPIKey);
               if(constatuscode2!=200)
                  {
               Serial.println("Error updating status to cloud. Error code: ");
               Serial.print(constatuscode2);
                  }
               else
                 {
                    digitalWrite(led2pin,HIGH);
                    Serial.println("Bedroom light is on");
                 }      
      case 103:
               constatuscode2=ThingSpeak.writeField( statusChannelNumber,statusled3FieldNumber,1,writestatusAPIKey);
               if(constatuscode2!=200)
                  {
               Serial.println("Error updating status to cloud. Error code: ");
               Serial.print(constatuscode2);
                  }
               else
                 {
                    digitalWrite(led3pin,HIGH);
                    Serial.println("Dining room light is on");
                 }
       case 104:
               constatuscode2=ThingSpeak.writeField( statusChannelNumber,statusfanFieldNumber,1,writestatusAPIKey);
               if(constatuscode2!=200)
                  {
               Serial.println("Error updating status to cloud. Error code: ");
               Serial.print(constatuscode2);
                  }
               else
                 {
                    for(int pos=0;pos<=180;pos+=10)
                      myservo.Write(pos);
                    for(int pos=180;pos<=0;pos--)
                      myservo.Write(pos);
                    Serial.println("fan is on");
                    delay(10000);
                 }  
       case 106:
               constatuscode2=ThingSpeak.writeField( statusChannelNumber,statusled1FieldNumber,0,writestatusAPIKey);
               if(constatuscode2!=200)
                  {
               Serial.println("Error updating status to cloud. Error code: ");
               Serial.print(constatuscode2);
                   }
               else
                 {
                    digitalWrite(led1pin,LOW);
                    Serial.println("living room light is off");
                  }   
        case 107: 
               constatuscode2=ThingSpeak.writeField( statusChannelNumber,statusled2FieldNumber,0,writestatusAPIKey);
               if(constatuscode2!=200)
                  {
               Serial.println("Error updating status to cloud. Error code: ");
               Serial.print(constatuscode2);
                  }
               else
                 {
                    digitalWrite(led2pin,LOW);
                    Serial.println("Bedroom light is off");
                 }  
        case 108:
               constatuscode2=ThingSpeak.writeField( statusChannelNumber,statusled3FieldNumber,0,writestatusAPIKey);
               if(constatuscode2!=200)
                  {
               Serial.println("Error updating status to cloud. Error code: ");
               Serial.print(constatuscode2);
                  }
               else
                 {
                    digitalWrite(led3pin,LOW);
                    Serial.println("Dining room light is off");
                 }
        case 109:
               constatuscode2=ThingSpeak.writeField( statusChannelNumber,statusfanFieldNumber,0,writestatusAPIKey);
               if(constatuscode2!=200)
                  {
               Serial.println("Error updating status to cloud. Error code: ");
               Serial.print(constatuscode2);
                  }
               else
                 {
                Serial.println("fan is on");
                 }
     }
  
}
 else
{
   Serial.println("Problem reading channel. HTTP error code: " )
   Serial.print(String(constatusCode1)); 
}
 
 delay(1000); // No need to read the temperature too often.


}


