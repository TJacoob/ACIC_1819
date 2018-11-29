void motionSensorR(){
  int buttonState = digitalRead(cellRButton);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonStateR) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      movementActionR(millis());
      sendMessage = true;
      setUpMessage(1,RX,RY);
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonStateR = buttonState;
}

void movementActionR(uint32_t t){
  brightnessR = 255;
  turnLightR = true;
  movementDetectedR = t;
}


void motionSensorL(){
  int buttonState = digitalRead(cellLButton);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonStateL) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      movementActionL(millis());
      sendMessage = true;
      setUpMessage(1,LX,LY);
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonStateL = buttonState;
}

void movementActionL(uint32_t t){
  brightnessL = 255;
  turnLightL = true;
  movementDetectedL = t;
}
