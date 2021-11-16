#include <Servo.h>

int brake = 0;    // amount of brake applied (current range is 0-1023)
int buttTO = 0;   // times out the drs button so it can be used later
int brakePin = 5; // pin the brake input is on
int buttPin = 7;  // pin that the button is on
int drsPin = 8;  // pin the output is on.
int drsButt = 0;  // status of the drs button
int attack = 50;  // angle of attack mode for servo
int defense = 0;  // angle of defense mode for servo
int servoPin = 3; // pin the servo is on
Servo lee;        // Choose lee. Theres a million lees. 

/* Pins on the arduino:
 *  Button:     7
 *  Brake :     A5
 *  DRS output: 8
 *  
 *  Ground for the potentimeter (brake) needs to be seperate
 *  from the common ground. It's very sensitve. 
 *  
 *  4 Pin buttons need to have 5v and GND on one side and CMD 
 *  on the other, also a 10kohm resistor on gnd is recomended.    
 *          _
 *   cmd - | | - GND
 *       - |_| - 5v
 */

void setup(){

  // DECLEARING PINS FOR INPUT/OUTPUT

  lee.attach(servoPin);     // putting lee on pin 3
  pinMode(drsPin, OUTPUT);  // The output (the blue lights rn)
  pinMode(brakePin, INPUT); // The input of the brake
  pinMode(drsButt, INPUT);  // the input of the DRS button
  //Serial.begin(9600);// for trouble shooting.
}

void loop(){
  
  // GETTING BRAKE AND BUTTON NUMBERS.
  
  brake = analogRead(brakePin);
  drsButt = digitalRead(buttPin);
  //Serial.println(); // for troubleshooting
  
  // NEXT, WAIT FOR THE RIGHT CONDITIONS.
  
  if (drsButt == 1 && brake == 0){        // checks to see if the brake is being pressed at all & button is pressed
    buttTO = 1;                           
    do {      
      if (buttTO == 1){ 
        drs(true);                        // This if statement sets a delay for the button.                       
        delay(250);                       // it allows a human to press the button, then unpress it.
        buttTO = 0;                       // The delay is .25 secs, which should be enough time.
      } 
      drs(true);                          // turns on drs
      brake = analogRead(brakePin);       // reads and sets brake and satus for next loop
      drsButt = digitalRead(buttPin);
      //Serial.println(drsButt);      

    }while(brake == 0 && drsButt != 1);   
    // DO THE ABOVE UNTIL THE BRAKE OR BUTTON IS PRESSED
    
    drs(false);                           // when brake or button is pressed, it breaks the loop and goes here. 
    delay(250);
  }
  drs(false);
}



void drs(bool status){   // WHAT HAPPENS WHEN DRS IS ENABLED?
  if (status == true){
    digitalWrite(drsPin, HIGH);    // if drs is on, send power through the drs pin.
    lee.write(attack);             // Attack mode
  }
  if (status == false){
    digitalWrite(drsPin, LOW);    // if drs is off, dont send power. 
    lee.write(defense);           // Defense mode
  }
}
