#include <Adafruit_Sensor.h> // include these three libraries (Adafruit_Sensor.h, DHT.h, DHT_U.h)
#include <DHT.h> 
#include <DHT_U.h>
DHT_Unified dht(2, DHT11);   // to define that sensor DHT11 is on pin 2
const int RedLedPin = 13; // to define that the red LED is on pin 13
const int GreenLedPin = 11; // to define that the green LED is on pin 11
const int MoisturePin = A0; // to define that moisture sensor is on pin A0
const int YellowLedPin = 12; // to define that the yellow LED is on pin 12
int Moisturevalue; //  to define the variable that represents the moisture's value
int DryValue = 466; // to define that the dryness threshold is set at 466. All results/values over 466 are considered as dry 

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600); // to set serial port data rate at 9600 bauds 
  dht.begin(); 
  pinMode (MoisturePin, INPUT); // defines moisture sensor as an input
  pinMode (RedLedPin, OUTPUT); // defines red led as an output
  pinMode (GreenLedPin, OUTPUT); // defines green led as an output
  pinMode (YellowLedPin, OUTPUT); // defines yellow led as an output
}

void loop() {
  // put your main code here, to run repeatedly:
  Moisturevalue = analogRead(MoisturePin); // reads the analog value of the moisture pin and affects it as moisture value 
  sensors_event_t event; // fetches the DHT sensor's values and affects them to the event variable
  dht.temperature().getEvent(&event); // translates the event's variable value in order to fetch all the temperatures' data
  if(event.temperature >= 30) // if temperature is above or equal to 30 
  {
    digitalWrite (RedLedPin, HIGH); // then red led turns on
    digitalWrite (GreenLedPin, LOW); // green led turns off
    digitalWrite(YellowLedPin, LOW); // and yellow led turns off too
  }
  else 
  {
    dht.humidity().getEvent(&event); // translates the event's variable value in order to fetch all the humidity's data
    if(event.relative_humidity <30) // if humidity value is under 30 
    {
       digitalWrite (RedLedPin, HIGH); // then red led turns on
       digitalWrite (GreenLedPin, LOW); // green led turns off
       digitalWrite(YellowLedPin, LOW); // and yellow led turns off
    }
    else if(Moisturevalue >= DryValue) // if moisture value is bigger or equal to dry value 
    {
      digitalWrite(YellowLedPin, HIGH); // it turns on the yellow LED
      digitalWrite(GreenLedPin, LOW); // it switches off the green LED
      digitalWrite (RedLedPin, LOW); // it switches off the red LED
    }
    else   // if not 
   {
      digitalWrite (GreenLedPin, HIGH); // it turns on the green LED
      digitalWrite(YellowLedPin, LOW); // it turns off the yellow LED
      digitalWrite (RedLedPin, LOW); // it turns off the red LED
   }
 }
}
