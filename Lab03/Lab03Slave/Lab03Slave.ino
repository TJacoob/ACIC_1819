// Includes
#include <Wire.h>

// Constants
const float roomTemp = 28.0;
const int errorMargin = 1.1;

float temperature = 0;
int ledSpeed = 500;
int light = 0;

void setup() {
  Serial.begin(9600);
  // Communications
  Wire.begin(8);
  Wire.onReceive(receiveData);

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
    float temp = Wire.read();
    if ( temp < (temperature-errorMargin) || temp > (temperature+errorMargin) )
    {
     temperature = temp;
     temperatureAction();
    }
    int li = Wire.read();
    if ( li != light )
    {
      light = li; 
      lightAction();
    }
    int led1 = Wire.read();
    int led2 = Wire.read();
    int led = led1*100+led2;
    if ( led != ledSpeed )
      ledSpeed = led;
    delay(ledSpeed);
    
  }
  Serial.println(temperature);
  Serial.println(ledSpeed);
  Serial.println(light);
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
