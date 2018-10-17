/*
  Arduino Starter Kit example
  Project 4 - Color Mixing Lamp

  This sketch is written to accompany Project 3 in the Arduino Starter Kit

  Parts required:
  - one RGB LED
  - three 10 kilohm resistors
  - three 220 ohm resistors
  - three photoresistors
  - red green and blue colored gels

  created 13 Sep 2012
  modified 14 Nov 2012
  by Scott Fitzgerald
  Thanks to Federico Vanzati for improvements

  http://www.arduino.cc/starterKit

  This example code is part of the public domain.
*/

const int greenLEDPin = 8;    // LED connected to digital pin 9
const int redLEDPin = 9;     // LED connected to digital pin 10
const int blueLEDPin = 10;    // LED connected to digital pin 11

const int sensorPin = A1;  // pin with the photoresistor

int value = 0;

int sensorValue = 0; // variable to hold the value from the red sensor

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // set the digital pins as outputs
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  // Read the sensors first:
  sensorValue = analogRead(sensorPin);

  // print out the values to the Serial Monitor
  Serial.print("\nRaw sensor Values: ");
  Serial.print(sensorValue);

  /*
    In order to use the values from the sensor for the LED, you need to do some
    math. The ADC provides a 10-bit number, but analogWrite() uses 8 bits.
    You'll want to divide your sensor readings by 4 to keep them in range
    of the output.
  */
  value = sensorValue / 4;

  // print out the mapped values
  Serial.print("\nMapped sensor Values: ");
  Serial.print(value);

  /*
    Now that you have a usable value, it's time to PWM the LED.
  */
  analogWrite(redLEDPin, value);
  analogWrite(greenLEDPin, value);
  analogWrite(blueLEDPin, value);
}
