#include "Wire.h"
    #include <Sparkfun_APDS9301_Library.h>

    APDS9301 apds;

    #define INT_PIN 2                
                                     
    bool lightIntHappened = false;   
                                     




#define _DEBUG_
#define _DISABLE_TLS_
#define THINGER_USE_STATIC_MEMORY
#define THINGER_STATIC_MEMORY_SIZE 512


#include <WiFi.h>
#include <ThingerWifi.h>


#define USERNAME "Guillaume"
#define DEVICE_ID "guillaumeid"
#define DEVICE_CREDENTIAL "0NB5y3AUK1jQ"


#define SSID "guillaume"                                         //network's name
#define SSID_PASSWORD "guillaume25"                              //network's password

ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(9600);
                                            
  thing.add_wifi(SSID, SSID_PASSWORD);                         // configure wifi network

  pinMode(LED_BUILTIN, OUTPUT);

  
  thing["test_nom"] << digitalPin(LED_BUILTIN);                //setup pin control turning on/off a light on the card

  
  thing["capteur lumiere"] >> [](pson& out){                    //setup the streaming data to the server
    out["luminous flux"] = apds.readCH0Level();
  };
  
  
  
  delay(5);                                                     // The CCS811 need  a brief delay after startup.
      Serial.begin(9600);
      Wire.begin();
    
                                                               // APDS9301 sensor setup.
      apds.begin(0x39);                                        // I2C default's address   
                                                    
      apds.setGain(APDS9301::LOW_GAIN);                        // Set the gain to low
                         
      apds.setIntegrationTime(APDS9301::INT_TIME_13_7_MS);     // Set the integration time to the shortest interval.
                        
      apds.setLowThreshold(0);                                 // Sets the low threshold to 0, effectively
                         
      apds.setHighThreshold(50);                               // Sets the high threshold to 500. This
                         
      apds.setCyclesForInterrupt(1);                           // A single reading in the threshold
                         
      apds.enableInterrupt(APDS9301::INT_ON);                  // Enable the interrupt.
      apds.clearIntFlag();
      
      
      

    
}

void loop() {
  thing.handle();
  thing.stream(thing["capteur lumiere"]);                       //send data to the server
   static unsigned long outLoopTimer = 0;
      apds.clearIntFlag();                          

      
      if (millis() - outLoopTimer >= 1000)                      // Print lux reading once-per-second
      {
        outLoopTimer = millis();
    
        Serial.print("Luminous flux: ");
        Serial.println(apds.readCH0Level(),6);                  //Print lux

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
