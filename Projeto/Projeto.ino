#include <Wire.h>

// Pins
const int cellRLed = 3;
const int cellRButton = 2;
const int cellLLed = 11;
const int cellLButton = 10;
const int lightSensor = A0;

// Consts
#define waitPeriod 6000
const int LX = 0;
const int LY = 0;
const int RX = LX+1;
const int RY = LY;

//int address = 9;
//int addressOut = 8;
#define CLOCKTIMEOUT 5000
boolean clockSent = false;


// Variables
int brightnessR = 0;
int brightnessL = 0;
int lastButtonStateR = 0;
int lastButtonStateL = 0;
boolean movementR = false;
uint32_t movementDetectedR = waitPeriod;
boolean movementL = false;
uint32_t movementDetectedL = waitPeriod;
uint32_t clockDelta = 0;
boolean clockSetup = false;
uint32_t timeNow ;

boolean turnLightR ;
boolean turnLightL ;
boolean sendMessage ;
boolean receivedMessage = false;

void setup() {
  pinMode(cellRLed,OUTPUT);
  pinMode(cellRButton,OUTPUT);
  pinMode(cellLLed,OUTPUT);
  pinMode(cellLButton,OUTPUT);
  Serial.begin(9600);
  //address = calcAddress(RX,RY);
  //Serial.println(address);
  Wire.begin(calcAddress(LX,LY));
  Wire.onReceive(receiveEvent);
  turnLightR = false;
  turnLightL = false;
  timeNow = millis();
}

void loop()
{
   // Send Clock to Neighbors
  if (!clockSent)
    sendClock();
  // If timeout, sync Clock
  if ( (millis()) > CLOCKTIMEOUT && (!clockSetup) )
    syncClock();

  //Serial.println("Timeouts");
  if( turnLightR )
    if( (timeNow)-movementDetectedR > waitPeriod)
      turnLightR = false;
  if ( turnLightL )
    if( (timeNow)-movementDetectedL > waitPeriod)
      turnLightL = false;
  sendMessage = false;

  //Serial.println("Sensors");
  brightnessSensor();  
  motionSensorR();
  motionSensorL();

  if ( receivedMessage )
    handleReceived();
  if ( sendMessage )
    sendToAll();

  //Serial.println("Actions");
  if ( turnLightR )
  {
    //brightnessR = 255;
    analogWrite(cellRLed, brightnessR);
  }  
  if ( turnLightL )
  {
    //brightnessL = 255;
    analogWrite(cellLLed, brightnessL);
  }


  timeNow = millis()-clockDelta;

  //delay(500);
}

void brightnessSensor()
{
  if ( !turnLightR )
  {
    brightnessR = 255-(analogRead(lightSensor)/4);
    turnLightR = true;
    if ( brightnessR > 64 )
      brightnessR = 64;  
    //brightnessR = 0;
  }
  if ( !turnLightL )
  {
    brightnessL = 255-(analogRead(lightSensor)/4);
    turnLightL = true;
    if ( brightnessL > 64 )
      brightnessL = 64;  
    //brightnessL = 0;
  }
  //Serial.println(brightnessL);
}
