void motionSensorR(){
  int buttonState = digitalRead(cellRButton);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonStateR) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      //movementActionR(timeNow);
      sendMessage = true;
      setUpMessage(1,RX,RY, timeNow);
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonStateR = buttonState;
}

void movementActionR(uint32_t t, int level){
  //Serial.println("Oh yea");
  brightnessR = intensity(level);
  turnLightR = true;
  movementDetectedR = t;
}


void motionSensorL(){
  int buttonState = digitalRead(cellLButton);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonStateL) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      //movementActionL(timeNow);
      sendMessage = true;
      setUpMessage(1,LX,LY, timeNow);
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonStateL = buttonState;
}

void movementActionL(uint32_t t, int level){
  //Serial.println("Shiim");
  brightnessL = intensity(level);
  turnLightL = true;
  movementDetectedL = t;
}

int intensity(int level)
{
  if ( level == 1 )
    return 64;       // Safety
  if ( level == 2 )
    return 128;      // Confort
  if ( level == 3 )
    return 255;      // Turned On
}
