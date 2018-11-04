// Includes
#include <Wire.h>
#include <stdio.h>
#include <string.h>

// Constants
const float roomTemp = 26.0;
const int errorMargin = 1.1;
char t[10]; //empty array where to put the numbers going to the master

float temperature = 0;
int ledSpeed = 500;
int light = 0;

void setup() {
  Serial.begin(9600);
  // Communications
  Wire.begin(8);
  Wire.onReceive(receiveData);
  Wire.onRequest(requestEvent);

  // Temperature LED
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
}

void loop() {
  ledBlink();
}

void receiveData(int i){
  while(1<=Wire.available()){
    char type = Wire.read();
    if ( type == 'T' )
    {
      int temp = Wire.read();  
      temperature = temp;
      Serial.println(temperature);
      temperatureAction();
    }
    if ( type == 'L' )
    {
      int temp = Wire.read();  
      light = temp;
      Serial.println(light);
      lightAction();
    }
    if ( type == 'P' )
    {
      int l1 = Wire.read();
      int l2 = Wire.read();  
      ledSpeed = l1*100+l2;
      Serial.println(ledSpeed);
    }
  }
  //Serial.println(temperature);
  //Serial.println(ledSpeed);
  //Serial.println(light);
  Serial.println("--------------");
}

void temperatureAction(){
  if (temperature >= roomTemp) 
    digitalWrite(4, HIGH);
  else
    digitalWrite(4, LOW);
}

void lightAction(){
  analogWrite(10, 255-light);    // B
}

void ledBlink(){ // Blink the LED
  digitalWrite(2, LOW);
  //Serial.println(ledSpeed);
  delay(ledSpeed);
  digitalWrite(2, HIGH);
  delay(ledSpeed);
}

void requestEvent() {
  Wire.write(t); 
}
