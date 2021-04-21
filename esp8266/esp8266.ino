#include "EmonLib.h"
#include <ESP8266WiFi.h>
#include "ESPAsyncUDP.h"

const char * ssid = "NeedSpeed";
const char * password = "ineedforspeed2018";
AsyncUDP udp;                  
EnergyMonitor emon1;
                   
#define ADC_INPUT A0
long prew=0;
double I;
unsigned long last_time =0;
unsigned long current_time =0;
double Wh = 0;
double V = 220;


void setup()
{  
  pinMode(ADC_INPUT, INPUT);
  Serial.begin(115200);
  emon1.current(ADC_INPUT, 109);
  
  WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Підключитись до WiFi не вдалось!");
        while(1) {delay(1000);}
    }    
           
}

void loop()
{
  if(millis()-prew>5000){
    prew=millis();
    double Current = emon1.calcIrms(1480);
    double P = V * Current;
    last_time = current_time;
    current_time = millis();
    Wh = P*((current_time -last_time)/3600000.0);
    sendtoweb(Current, Wh);
    Serial.println(Current);
    Serial.println(Wh);
    char buffer[15];
    dtostrf(Current, 5, 2, buffer);
    udp.broadcastTo(buffer, 1234);
    }
}
