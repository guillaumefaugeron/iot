/*
 * Workshop 3
 * By Julien Khabbaz, guillaume Faugeron, Quentin Fayet
 * On the loop we have two functions. 
 * We will blink a red LED if the temperature is too high or the humidity is too low.
 * And we will switch on a yellow LED if the moisture is dry.
 */

#include <Adafruit_Sensor.h>                         // include these three libraries (Adafruit_Sensor.h, DHT.h, DHT_U.h)
#include <DHT.h> 
#include <DHT_U.h>

DHT_Unified dht(2, DHT11);                           // to define that sensor DHT11 is on pin 2

#define RED_LED_PIN 13                               // to define that the red LED is on pin 13
#define GREEN_LED_PIN 11                             // to define that the green LED is on pin 11
#define YELLOW_LED_PIN 12                            // to define that the yellow LED is on pin 12
#define MOISTURE_PIN A0                              // to define that moisture sensor is on pin A0

int moistureValue;                                   //  to define the variable that represents the moisture's value
int dryValue = 466;                                  // to define that the dryness threshold is set at 466. All results/values over 466 are considered as dry 

void setup()                                         // put your setup code here, to run once:
{
  Serial.begin(9600);                                // to set serial port data rate at 9600 bauds 
  dht.begin(); 
  pinMode(MOISTURE_PIN, INPUT);                      // defines moisture sensor as an input
  pinMode(RED_LED_PIN, OUTPUT);                      // defines red led as an output
  pinMode(GREEN_LED_PIN, OUTPUT);                    // defines green led as an output
  pinMode(YELLOW_LED_PIN, OUTPUT);                   // defines yellow led as an output
}

void loop()                                          // put your main code here, to run repeatedly:
{
  sensors_event_t event;                             // fetches the DHT sensor's values and affects them to the event variable
  dht.temperature().getEvent(&event);                // translates the event's variable value in order to fetch all the temperatures' data
  if(event.temperature >= 30)                        // if temperature is above or equal to 30 
    {
      digitalWrite(RED_LED_PIN, HIGH);               // then red led turns on
      digitalWrite(GREEN_LED_PIN, LOW);              // green led turns off
      digitalWrite(YELLOW_LED_PIN, LOW);             // and yellow led turns off too
    }
  else 
    {
      dht.humidity().getEvent(&event);               // translates the event's variable value in order to fetch all the humidity's data
      if(event.relative_humidity <30)                // if humidity value is under 30 
        {
          digitalWrite(RED_LED_PIN, HIGH);           // then red led turns on
          digitalWrite(GREEN_LED_PIN, LOW);          // green led turns off
          digitalWrite(YELLOW_LED_PIN, LOW);         // and yellow led turns off
        }
      else
        {
          moistureValue = analogRead(MOISTURE_PIN);  // reads the analog value of the moisture pin and affects it as moisture value  
          if(moistureValue >= dryValue)              // if moisture value is bigger or equal to dry value 
            {
              digitalWrite(YELLOW_LED_PIN, HIGH);    // it turns on the yellow LED
              digitalWrite(GREEN_LED_PIN, LOW);      // it switches off the green LED
              digitalWrite(RED_LED_PIN, LOW);        // it switches off the red LED
            }
          else   // if not 
            {
              digitalWrite(GREEN_LED_PIN, HIGH);     // it turns on the green LED
              digitalWrite(YELLOW_LED_PIN, LOW);     // it turns off the yellow LED
              digitalWrite(RED_LED_PIN, LOW);        // it turns off the red LED
            }
        }
    }
}
