int statesRight[STATEBUFFERSIZE];      // Array of states
unsigned long timesRight[STATEBUFFERSIZE];  // Array of times matching each state

int lastButtonStateR = 0;

// Progresses the cell state each loop
// Public Function, returns the current cell State
int cellStepRight()
{
  if ( timesRight[0] == 0 && timesRight[1] != 0 )
    return statesRight[0];
  if ( timesRight[0] == 0 )
    return 0;
  if( (timeNow-timesRight[0])>WAITPERIOD )
    stepArrayRight();
  else
    return statesRight[0]; 
}

// Public Function, add a state to the Right cell array
void addStateRight(int state, unsigned long t)   // Adds element to the first free spot of the array
{
  int pos = 0;
  if ( state > statesRight[0] )
  {
    pullArrayRight();
    statesRight[0] = state;
    timesRight[0] = t;
  } 
  else
  {
    for ( int x = 0; x<STATEBUFFERSIZE; x++)
      if ( timesRight[x] == 0 )
      {
        pos = x;
        break;
      }
    statesRight[pos] = state;
    if ( state == 0 )
      timesRight[pos] = 0;
    else
      timesRight[pos] = t;
  }
}

// Private Function, rearranges the array (Shift Right)
void stepArrayRight(){
  //Serial.println("Shift Right");
  //printBufferRight();
  for ( int x = 0; x < STATEBUFFERSIZE-1 ; x++ ) // Pulls remaining objects to one behind
    statesRight[x] = statesRight[x+1];   
  for ( int x = 0; x < STATEBUFFERSIZE-1 ; x++ ) // Pulls remaining objects to one behind
    timesRight[x] = timesRight[x+1];
}

// Private Function, rearranges the array (Shift Right)
void pullArrayRight(){
  
  for ( int x = STATEBUFFERSIZE; x > 0 ; x-- ) // Pulls remaining objects to one behind
    statesRight[x] = statesRight[x-1];   
  for ( int x = STATEBUFFERSIZE; x > 0 ; x-- ) // Pulls remaining objects to one behind
    timesRight[x] = timesRight[x-1];
  //Serial.println("Shift Right");
  
}

void printBufferRight()
{
  for ( int x = 0; x<STATEBUFFERSIZE; x+=1)
  {
    Serial.print("For buffer= ");Serial.println(x);
    Serial.print("STATE: ");Serial.println(statesRight[x]);
    Serial.print("TIME: ");Serial.println(timesRight[x]);
  }
}

// Detects a Click on the Button
void motionSensorRight(){
  int buttonState = digitalRead(cellRButton);
  if (buttonState != lastButtonStateR) {
    if (buttonState == HIGH) {
      // Send Message to Everyone
      spreadMovement(RX,RY, timeNow);
    }
    delay(50);
  }
  lastButtonStateR = buttonState;
}

// Lights Up the LED according to the state
void ledRight(int state)
{
  int brightness;
  if ( state == 0 ) 
  {
    brightness = 255-(analogRead(lightSensor)/4);
    if ( brightness > 64 )
      brightness = 64;  
  }
  else if ( state == 1 )  // Safety
    brightness = 64;
  else if ( state == 2 )  // Comfort
    brightness = 127;
  else if ( state == 3 )  // On
    brightness = 255;
    
  analogWrite(cellRLed, brightness);
}
