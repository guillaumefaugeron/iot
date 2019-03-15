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
  Serial.begin(115200);                                             //definition de la vitesse du port serie a 115200 bauds 

  //Defintion entre sortie
  pinMode(ledPin, OUTPUT);                                          
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(interruptPin, blink, CHANGE);             //defintion attach interupt
}

void loop() {
  incomingByte = Serial.read();                         //affecte a incomingByte la valeur ascii de la touche appuyer

    if(incomingByte == 111)                               //si incomingByte == 111 (soit la touche 'o')
    {
      analogWrite(ledPin, potentiometerState);          //allmer la led a la valeur du potentiometre
      ledLow = true;                               //change la valeur de la variable ledLow
    }
    else if(incomingByte == 79)                 //sinon si incomingByte == 79 (soit 'O')
    {
        ledLow = false;                         //changer la valeur de la variable
    }

    if(ledLow == false)                       //if ledlow est a false 
    {
        digitalWrite(ledPin, LOW);          //eteindre la led
        return;                           //recomencer le code
    }
  
  potentiometerState = analogRead(potentiometerPin);        //lire potentiometerPin et affecter sa valeur a potentiometerState
  potentiometerState = potentiometerState/4;              //diviser la valeur de potentiometerstate par 4 pour l'adapter a la led
  Serial.println(potentiometerState);                       //afficher la valeur du potentiometre
  if(state == LOW)                                    //si state est au niveau bas
  {
    analogWrite(ledPin, potentiometerState);          //allumer la d=ked a la valeur du potentiometre
  }
  else                                                  //sinon
  {
    analogWrite(ledPin, potentiometerState);          //faire clignoter la led a la valeur du potentiometre, toute les une seconde
    delay(1000);
    analogWrite(ledPin, 0);
    delay(1000);
  }
}

void blink() {                          //création de la void blink qui fait changer d'etat la var state
  state = !state;
}
