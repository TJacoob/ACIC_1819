#include <Wire.h>

// PINS
#define cellLLed 11
#define cellLButton 10
#define cellRLed 3
#define cellRButton 2
#define lightSensor A0

// COORDINATES
#define LX 0
#define LY 0
#define RX LX+1
#define RY LY

// CONSTANTS
#define WAITPERIOD 4000
#define CLOCKTIMEOUT 5000
#define STATEBUFFERSIZE 5

// VARIABLES
unsigned long timeNow;
int ledStateLeft ;
int ledStateRight ;
boolean messageToBeSent = false;

void setup() {
  pinMode(cellRLed,OUTPUT);
  pinMode(cellRButton,OUTPUT);
  pinMode(cellLLed,OUTPUT);
  pinMode(cellLButton,OUTPUT);
  Serial.begin(9600);
  
  //addState(0,millis());
  //printBufferLeft();
}

void loop() {

  // RIGHT
  
  motionSensorRight();

  
  ledStateRight = cellStepRight();
  //Serial.println(ledStateLeft);
  ledRight(ledStateRight);

  
  // LEFT
  motionSensorLeft();
  

  // Ler Mensagens();

  ledStateLeft = cellStepLeft();
  //Serial.println(ledStateLeft);
  ledLeft(ledStateLeft);

  if ( messageToBeSent )
  {
    for ( int x=-1; x<=1; x++)
      for ( int y=-1; y<=1; y++)
        sendMessage(LX+x,LY+y);
    messageToBeSent = false;
  } 

  
  //Serial.println(millis());
  timeNow = millis();
  //Serial.println(timeNow);
}


// Auxiliary Functions
int decodeCoordX(int dec)
{ return (dec%8); } 
int decodeCoordY(int dec)
{ return (dec-decodeCoordX(dec))/16; }
