#include "Wire.h"
    #include <Sparkfun_APDS9301_Library.h>

    APDS9301 apds;

    #define INT_PIN 2 // We'll connect the INT pin from our sensor to the
                      // INT0 interrupt pin on the Arduino.
    bool lightIntHappened = false; // flag set in the interrupt to let the
                     //  mainline code know that an interrupt occurred.




#define _DEBUG_
#define _DISABLE_TLS_
#define THINGER_USE_STATIC_MEMORY
#define THINGER_STATIC_MEMORY_SIZE 512


#include <WiFi.h>
#include <ThingerWifi.h>


#define USERNAME "Guillaume"
#define DEVICE_ID "guillaumeid"
#define DEVICE_CREDENTIAL "0NB5y3AUK1jQ"


#define SSID "guillaume"
#define SSID_PASSWORD "guillaume25"

ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(9600);
  // configure wifi network
  thing.add_wifi(SSID, SSID_PASSWORD);

  pinMode(LED_BUILTIN, OUTPUT);

  // pin control example (i.e. turning on/off a light, a relay, etc)
  thing["test_nom"] << digitalPin(LED_BUILTIN);

  
  thing["capteur lumiere"] >> [](pson& out){
    out["luminous flux"] = apds.readCH0Level();
  };
  
  
  
  delay(5);    // The CCS811 need  a brief delay after startup.
      Serial.begin(9600);
      Wire.begin();
    
      // APDS9301 sensor setup.
      apds.begin(0x39);  // We're assuming you haven't changed the I2C
                         //  address from the default by soldering the
                         //  jumper on the back of the board.
      apds.setGain(APDS9301::LOW_GAIN); // Set the gain to low. Strictly
                         //  speaking, this isn't necessary, as the gain
                         //  defaults to low.
      apds.setIntegrationTime(APDS9301::INT_TIME_13_7_MS); // Set the
                         //  integration time to the shortest interval.
                         //  Again, not strictly necessary, as this is
                         //  the default.
      apds.setLowThreshold(0); // Sets the low threshold to 0, effectively
                         //  disabling the low side interrupt.
      apds.setHighThreshold(50); // Sets the high threshold to 500. This
                         //  is an arbitrary number I pulled out of thin
                         //  air for purposes of the example. When the CH0
                         //  reading exceeds this level, an interrupt will
                         //  be issued on the INT pin.
      apds.setCyclesForInterrupt(1); // A single reading in the threshold
                         //  range will cause an interrupt to trigger.
      apds.enableInterrupt(APDS9301::INT_ON); // Enable the interrupt.
      apds.clearIntFlag();
      
      
      

    
}

void loop() {
  thing.handle();
  thing.stream(thing["capteur lumiere"]);
   static unsigned long outLoopTimer = 0;
      apds.clearIntFlag();                          

      // This is a once-per-second timer that calculates and prints off
      //  the current lux reading.
      if (millis() - outLoopTimer >= 1000)
      {
        outLoopTimer = millis();
    
        Serial.print("Luminous flux: ");
        Serial.println(apds.readCH0Level(),6);

        if (lightIntHappened)
        {
          Serial.println("Interrupt");
          lightIntHappened = false;
        }
      }
      
      
      


  
} 


 void lightInt()
    {
      lightIntHappened = true;
    }