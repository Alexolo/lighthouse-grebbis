#include <SPI.h>
#include <Wire.h>
#include <RtcDS3231.h>  //RTC library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <aREST.h>
#include "config.h"
#include "config_wifi.h"


unsigned long startMillis;
unsigned long currentMillis;
unsigned long loopInterval = 250;


//RtcDS3231 rtcObject;              //Uncomment for version 1.0.1 of the rtc library
RtcDS3231<TwoWire> rtcObject(Wire); //Uncomment for version 2.0.0 of the rtc library

aREST rest = aREST();
WiFiServer server(LISTEN_PORT);

void setup()   {
  Serial.begin(115200);
  startMillis = millis();
  
  // Setup Wifi and other components
  wifiConnect();
  relaySetup();
  rtcObject.Begin();

  wifiPrintStatus();
  clockPrintTime();

  rest.set_id("1");
  rest.set_name("esp8266-lighthouse");
  rest.function("test", restFunction);
  server.begin();

  // Check that time is correct and has not deviated to much
  //clockSet(16, 05, 18, 21, 20, 0);


  Serial.println("Setup complete");

}

int restFunction(String command) {
  Serial.println(command);
  
    
  relaySetBlinkIntervals(command.substring(0,1).toInt(), command.substring(1,2).toInt(),command.substring(2,3).toInt());
  return 1;
}

bool test = true;

void loop() {
  currentMillis = millis();
  if (currentMillis - startMillis >= loopInterval) {
    Serial.print(".");
    clockPrintTime();

    WiFiClient client = server.available();
    if (client) {
      rest.handle(client);
    }

    if (currentMillis > 10000 && test) {
      // Tests the relay once, blinking 3 times, 4s on, 2s off
      test = false;
      //relaySetBlinkIntervals(3, 4, 2);
      int current = wifiGetCurrentTime();
      clockSet(current);
      
    }
    relayDoBlinkIntervals();

    //Serial.println(clockGetDateTime());
    startMillis = currentMillis;
  
  
  }
}


