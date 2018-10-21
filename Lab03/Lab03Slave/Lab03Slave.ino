// Includes
#include <Wire.h>

// Constants
const float roomTemp = 28.0;

int temperature = 0;

void setup() {
  Serial.begin(9600);
  // Communications
  Wire.begin(8);
  Wire.onReceive(temperatureAction);
  
  // Temperature LED
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("asdasd\n");
}

void temperatureAction(int i){
  while(1<=Wire.available()){
    int temp = Wire.read();
    Serial.println(temp);
    temperature = temp;
  }
  
  //Serial.print("asdas");
  if (temperature >= roomTemp) 
    digitalWrite(4, HIGH);
  else
    digitalWrite(4, LOW);
}
