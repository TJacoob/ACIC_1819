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
boolean messageReceived = false;

uint32_t clockDelta = 0;
boolean clockSetup = false;
boolean clockSent = false;

void setup() {
  pinMode(cellRLed,OUTPUT);
  pinMode(cellRButton,OUTPUT);
  pinMode(cellLLed,OUTPUT);
  pinMode(cellLButton,OUTPUT);
  Serial.begin(9600);
  
  Wire.begin(calcAddress(LX,LY));
  Wire.onReceive(receiveEvent);

  //addStateRight(1,1);
  //addStateLeft(1,1);
  //printBufferLeft();
}

void loop() {

  // Send Clock to Neighbors
  if (!clockSent)
    sendClock();
  // If timeout, sync Clock
  if ( (millis()) > CLOCKTIMEOUT && (!clockSetup) )
    syncClock();


  ledStateLeft = cellStepLeft();
  //Serial.println(ledStateLeft);
  ledLeft(ledStateLeft);

   ledStateRight = cellStepRight();
  //Serial.println(ledStateLeft);
  ledRight(ledStateRight);
  
  // RIGHT
  
  motionSensorRight();
    
  if ( messageToBeSent )
  {
    for ( int x=-1; x<=1; x++)
      for ( int y=-1; y<=1; y++)
        sendMessage(RX+x,RY+y);
    messageToBeSent = false;
  } 

    // LEFT
  motionSensorLeft();

  if ( messageToBeSent )
  {
    for ( int x=-1; x<=1; x++)
      for ( int y=-1; y<=1; y++)
        sendMessage(LX+x,LY+y);
    messageToBeSent = false;
  } 

  if ( messageReceived ){
    handleReceived();
    messageReceived = false;
  }

 

  delay(50);
  
  
  //Serial.println(millis());
  timeNow = millis();
  //Serial.println(timeNow);
}


// Auxiliary Functions
int decodeCoordX(int dec)
{ return (dec%8); } 
int decodeCoordY(int dec)
{ return (dec-decodeCoordX(dec))/16; }
