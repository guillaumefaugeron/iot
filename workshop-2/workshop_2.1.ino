
//WORKSHOP 2//
//YNOV - Informatique ingé-sup//
//Julien KHABBAZ - Guillaume FAYET - Quentin FAYET//
//year 2018 - 2019//

//affectation des pin
const byte ledPin = 10;      
const byte interruptPin = 2;
const int potentiometerPin = A0;

//affectation des variable
int incomingByte = 0; 
volatile byte state = LOW;
int potentiometerState;
bool ledLow = true;

void setup() {
  Serial.begin(115200);                                             //Set serial port's data rate at 115200 bps 

  //Defintion entre sortie
  pinMode(ledPin, OUTPUT);                                          
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(interruptPin, blink, CHANGE);             
}

void loop() {
incomingByte = Serial.read();                         //Affect to incomingByte the ascii value of the pressed key

    if(incomingByte == 111)                               //if incomingByte == 111 (being the 'o' key)
    {
      analogWrite(ledPin, potentiometerState);          //turn on led according to the potentiometer's value
      ledLow = true;                               //changes the value of ledLow variable
    }
    else if(incomingByte == 79)                 //else if incomingByte == 79 (being 'O')
    {
        ledLow = false;                         //change the variable's value

    if(ledLow == false)                       //if ledlow is false 
    {
        digitalWrite(ledPin, LOW);          //turn off led
        return;                           //restart code
    }
  
  potentiometerState = analogRead(potentiometerPin);        //read potentiometerPin and affect its value according to potentiometerState
  potentiometerState = potentiometerState/4;              //divides the value of the potentiometerstate by 4 in order for it to adapt according to the led
  Serial.println(potentiometerState);                       //print the potentiometer's value 
  if(state == LOW)                                    //if state is at the lower level
  {
    analogWrite(ledPin, potentiometerState);          //turn on led according to the potentiometer's value
  }
  else                                                  //else
  {
    analogWrite(ledPin, potentiometerState);          //makes the led blink according to the value of the potentiometer, every second
    delay(1000);
    analogWrite(ledPin, 0);
    delay(1000);
  }
}

void blink() {                          //void blink set up which changes the state of the var state
  state = !state;
}
