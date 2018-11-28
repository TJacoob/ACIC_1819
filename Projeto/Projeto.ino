#include <Wire.h>

// Pins
const int cellRLed = 3;
const int cellRButton = 2;
const int cellLLed = 11;
const int cellLButton = 10;
const int lightSensor = A0;

// Consts
const int waitPeriod = 10000;
const int RX = 1;
const int RY = 0;
const int LX = 0;
const int LY = 0;
int address;

// Variables
int brightnessR = 0;
int brightnessL = 0;
int lastButtonStateR = 0;
int lastButtonStateL = 0;
boolean movementR = false;
long movementDetectedR = 0;
boolean movementL = false;
long movementDetectedL = 0;
/*
int fadeAmount = 5;

boolean light = true;

int buttonPushCounter = 0;
*/

void setup() {
  pinMode(cellRLed,OUTPUT);
  pinMode(cellRButton,OUTPUT);
  pinMode(cellLLed,OUTPUT);
  pinMode(cellLButton,OUTPUT);
  Serial.begin(9600);
  address = calcAddress(RX,RY);
  //Serial.println(address);
  Wire.begin(address);
  Wire.onReceive(receiveEvent);
}

void loop() {
  if( movementR )
  {
    sendComms();
    if(millis()-movementDetectedR > waitPeriod)
      movementR = false;
      brightnessR = 255;
  }
  if( movementL )
  {
    sendComms();
    if(millis()-movementDetectedL > waitPeriod)
      movementL = false;
      brightnessL = 255;
  }

  //EnviarComunicações()
  //sendComms();
  analogWrite(cellRLed, brightnessR);
  analogWrite(cellLLed, brightnessL);
  
  brightnessSensor();
  //ReceberCommunicações()
  motionSensorR();
  motionSensorL();
  
  
}

void motionSensorR(){
  int buttonState = digitalRead(cellRButton);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonStateR) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      brightnessR = 255;
      movementR = true;
      movementDetectedR = millis();
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonStateR = buttonState;
}

void motionSensorL(){
  int buttonState = digitalRead(cellLButton);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonStateL) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      brightnessL = 255;
      movementL = true;
      movementDetectedL = millis();
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonStateL = buttonState;
}

void brightnessSensor()
{
  brightnessR = 255-(analogRead(lightSensor)/4);
  if ( brightnessR > 64 )
    brightnessR = 64;
  brightnessL = 255-(analogRead(lightSensor)/4);
  if ( brightnessL > 64 )
    brightnessL = 64;
  Serial.println(brightnessL);
}

int calcAddress(int x, int y)
{
  int mid = x/2;
  int result = (mid*16)+y;
  return result;
}

void sendComms()
{
  //Serial.println("In");
  Wire.beginTransmission(address);
  //Serial.println("MiddleIn");
  Wire.write(true);
  //Serial.println("MiddleOut");
  Wire.endTransmission(); 
  //Serial.println("Out");
}

void receiveEvent(int howMany){
 while (Wire.available() > 0){
   boolean b = Wire.read();
   Serial.print("CENAAAAAAS: ");
   Serial.println(b, DEC);
   //digitalWrite(LED, !b);
 }
 Serial.println("Finish"); 
}
