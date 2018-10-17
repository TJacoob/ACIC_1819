/*
  Arduino Starter Kit example
  Project 5 - Servo Mood Indicator

  This sketch is written to accompany Project 5 in the Arduino Starter Kit

  Parts required:
  - servo motor
  - 10 kilohm potentiometer
  - two 100 uF electrolytic capacitors

  created 13 Sep 2012
  by Scott Fitzgerald

  http://www.arduino.cc/starterKit

  This example code is part of the public domain.
*/

int const potPin = A3; // analog pin used to connect the potentiometer
int potVal;  // variable to read the value from the analog pin
int value;

void setup() {
  Serial.begin(9600); // open a serial connection to your computer
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  potVal = analogRead(potPin); // read the value of the potentiometer
  // print out the value to the Serial Monitor
  Serial.print("\npotVal: ");
  Serial.print(potVal);

  // scale the numbers from the pot
  value = map(potVal, 0, 1023, 0, 100);

  // print out the angle for the servo motor
  //Serial.print(", angle: ");
  //Serial.println(angle);

  if ( value < 50 )
    digitalWrite(2, LOW); 
  if ( value > 50 )
    digitalWrite(2, HIGH);

  // wait for the servo to get there
  //delay(15);
}
