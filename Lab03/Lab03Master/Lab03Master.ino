// Includes
#include <Wire.h>
#include <time.h>

// Pins
const int pinTemp = A0;
const int pinLight = A1;
const int pinPoten = A3;

// Constants
const int errorMargin = 5;
const float roomTemp = 26.0;
const int samples = 5;
int ledSpeed = 500;
int light = 0;
int oldTime = 0;

// Last Values Sampled
// The goal is to only run the data handling when there is a new value in the pin
// We also have an "error margin" to counterbalance the current fluctuations
int lastTemp = 0;
int temperature = 0;
int lastPoten = 0;
int lastLight = 0;

void setup() {
  Serial.begin(9600);
  // Temperature LED
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  // Potentiometer LED
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  // RGB Led
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  // Communications
  Wire.begin();
}

void loop() {
  // Round-Robin Architecture
  // Communications

  time_t send_t = millis();
  //Serial.println(send_t);
  Wire.requestFrom(8, 3);    // request 3 bytes from slave device #8
 
  // Temperature
  if ( analogRead(pinTemp) < (lastTemp-errorMargin) || analogRead(pinTemp) > (lastTemp+errorMargin) )
  {
    Serial.print("Sent Temperature: ");
    Serial.println(temperature);
    temperatureSensor();
    sendTemperatureData();
  }
  // Potentiometer
  if ( analogRead(pinPoten) < (lastPoten-errorMargin) || analogRead(pinPoten) > (lastPoten+errorMargin) )
  {
    //Serial.println("Sent Temperature");
    potentiometer();
    sendPotenData();
  }
  //ledBlink();
    //Serial.println(lastLight);
    //Serial.println(analogRead(pinLight)/4);
  // Light Sensor
  if ( analogRead(pinLight)/4 < (lastLight-errorMargin) || analogRead(pinLight)/4 > (lastLight+errorMargin) )
  {
    Serial.println("Sent Light");
    lightSensor();
    sendLightData();
  }

  time_t receive_t = millis();
  Serial.println( receive_t-send_t );
  
}

// Temperature Functions
void temperatureSensor() {
  int sensorAvg = 0;
  for ( int i=0; i<samples; i++)
    sensorAvg += analogRead(pinTemp);   // Read Pin
  int sensorVal = sensorAvg/samples;
  lastTemp = sensorVal;   // Store value to check for changes in the loop
  temperature =  (((sensorVal/1024.0)*5.0)-0.508)*100; // Data Conversion
  //Serial.print("Temperature: ");
  //Serial.println(temperature);
  //if (temperature >= roomTemp) 
    //digitalWrite(4, HIGH);
  //else
    //digitalWrite(4, LOW);
}

// Potentiometer Functions
void potentiometer(){
  int sensorAvg = 0;
  for ( int i=0; i<samples; i++)
    sensorAvg += analogRead(pinPoten);   // Read Pin
  int potenVal = sensorAvg/samples;
  lastPoten = potenVal; // Store value to check for changes in the loop
  //Serial.print("Potence: ");
  //Serial.println(potenVal);
  // Maping out the ledspeed between 200ms and 1400ms to match
  // the outcome of the potentiometer
  ledSpeed = map(potenVal, 0, 1023, 200, 1400);
  //Serial.print("LED Speed: ");
  //Serial.println(ledSpeed);
}

void ledBlink(){ // Blink the LED
  digitalWrite(2, LOW);
  delay(ledSpeed);
  digitalWrite(2, HIGH);
  delay(ledSpeed);
}

// Light Functions
void lightSensor(){
  int sensorAvg = 0;
  for ( int i=0; i<samples; i++)
    sensorAvg += analogRead(pinLight);   // Read Pin
  int sensorLight = sensorAvg/samples;
  //Serial.print("Sensor Light: ");
  //Serial.println(sensorLight);
  lastLight = sensorLight / 4;      // Store value to check for changes in the loop
  light = sensorLight / 4;    // Transform from 1024 to 255
  //Serial.print("light: ");
  //Serial.println(255-light);
  //analogWrite(8, 255-light);   // R
  //analogWrite(9, 255-light);   // G
  analogWrite(10, 255-light);    // B
}

void sendTemperatureData(){
  Wire.beginTransmission(8);
  Wire.write('T');
  Wire.write(temperature);  
  Wire.endTransmission();
}

void sendLightData(){
  Wire.beginTransmission(8);
  Wire.write('L');
  Wire.write(light);  
  Wire.endTransmission();
}

void sendPotenData(){
  Wire.beginTransmission(8);
  Wire.write('P');
  int ledSpeed1 = int(ledSpeed/100);
  int ledSpeed2 = ledSpeed%100;
  Wire.write(ledSpeed1);
  Wire.write(ledSpeed2);  
  Wire.endTransmission();
}
