#include <Servo.h>
Servo andrew;         //just use andrew, there are a million andrews

void setup() {
  andrew.attach(3);   // attaches andrew to pin 3 on the arduino
}

void loop() {
  /* What we want this code to do is prove that 
   * this arduino can move a servo. The servo I'm
   * using is drawing too much power, so maybe don't
   * directly wire a Hitech HS-815BB+ directly into 
   * an adruino. */ 

   // move the servo, wait like 5 seconds, move it again.

   andrew.write(0); // go to 0 degree angle
   delay(5000); // 5 seconds or 5k ms
   andrew.write(100); // go to 100 degree maybe? angle
   delay(5000); // 
}
