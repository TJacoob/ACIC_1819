// Pins
const int cellRightLed = 3;
const int cellRightButton = 2;
const int cellLeftLed = 11;
const int cellLeftButton = 10;
const int lightSensor = A0;

// Consts
const int waitPeriod = 3000;

// Variables
int brightness = 0;
int buttonState = 0;
int lastButtonState = 0;
boolean movement = false;
long movementDetected = 0;
/*
int fadeAmount = 5;

boolean light = true;

int buttonPushCounter = 0;
*/

void setup() {
  pinMode(cellRightLed,OUTPUT);
  pinMode(cellRightButton,OUTPUT);
  pinMode(cellLeftLed,OUTPUT);
  pinMode(cellLeftButton,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if( movement )
  {
    if(millis()-movementDetected > waitPeriod)
      movement = false;
  }
  else
  {
    brightnessSensor();
    //ReceberCommunicações()
    motionSensor();
  }
  //EnviarComunicações()
  analogWrite(cellRightLed, brightness);
}

void motionSensor(){
  buttonState = digitalRead(cellRightButton);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      brightness = 255;
      movement = true;
      movementDetected = millis();
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
}

void brightnessSensor()
{
  brightness = 255-(analogRead(lightSensor)/4);
  if ( brightness > 64 )
    brightness = 64;
  //Serial.println(brightness);
}
