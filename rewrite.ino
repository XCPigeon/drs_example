int brake = 0;       // amount of brake applied (current range is 0-1023)
int buttTO = 0;      // times out the drs button so it can be used later
int brakePin = 5;    // pin the brake input is on
int buttPin = 7;     // pin that the button is on
int drsPin = 12;     // pin the output is on.
int drsButt = 0;     // status of the drs button
bool isItOn = false; // Is drs on?

void setup() {
  pinMode(drsPin, OUTPUT);  // The output (the blue lights rn)
  pinMode(brakePin, INPUT); // The input of the brake
  pinMode(drsButt, INPUT);  // the input of the DRS button
  Serial.begin(9600);
}

void loop() {
  buttTO=1;
  while (drsButt == 1 && brake == 0 && buttTO > 0){
    Serial.println("time out");
    drs(true);
    delay(250);
  }
  while (drsButt == 0 && brake == 0 && buttTO == 0){
    drs(true);
    Serial.println("GO!");
  }
  drs(false);
  Serial.println("Searching...");
}

void drs(bool status){
  if (status == true){
    digitalWrite(drsPin, HIGH);
    brake = analogRead(brakePin);
    drsButt = digitalRead(buttPin);
    isItOn = true; 
    buttTO--;
  }
  if (status == false){
    digitalWrite(drsPin, LOW);
    brake = analogRead(brakePin);
    drsButt = digitalRead(buttPin);
    isItOn = false; 
  }
}
