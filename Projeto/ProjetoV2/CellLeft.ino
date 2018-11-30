int statesLeft[STATEBUFFERSIZE];      // Array of states
unsigned long timesLeft[STATEBUFFERSIZE];  // Array of times matching each state

int lastButtonStateL = 0;

// Progresses the cell state each loop
// Public Function, returns the current cell State
int cellStepLeft()
{
  if ( timesLeft[0] == 0 && timesLeft[1] != 0 )
    return statesLeft[0];
  if ( timesLeft[0] == 0 )
    return 0;
  if( (timeNow-timesLeft[0])>WAITPERIOD )
    stepArrayLeft();
  else
    return statesLeft[0]; 
}

// Public Function, add a state to the Left cell array
void addStateLeft(int state, unsigned long t)   // Adds element to the first free spot of the array
{
  int pos = 0;
  if ( state >= statesLeft[0] )
  {
    pullArrayLeft();
    statesLeft[0] = state;
    timesLeft[0] = t;
  } 
  else
  {
    for ( int x = 0; x<STATEBUFFERSIZE; x++)
      if ( timesLeft[x] == 0 )
      {
        pos = x;
        break;
      }
    statesLeft[pos] = state;
    if ( state == 0 )
      timesLeft[pos] = 0;
    else
      timesLeft[pos] = t;
  }
}

// Private Function, rearranges the array (Shift Left)
void stepArrayLeft(){
  //Serial.println("Shift Left");
  //printBufferLeft();
  for ( int x = 0; x < STATEBUFFERSIZE-1 ; x++ ) // Pulls remaining objects to one behind
    statesLeft[x] = statesLeft[x+1];   
  for ( int x = 0; x < STATEBUFFERSIZE-1 ; x++ ) // Pulls remaining objects to one behind
    timesLeft[x] = timesLeft[x+1];
}

// Private Function, rearranges the array (Shift Right)
void pullArrayLeft(){
  
  for ( int x = STATEBUFFERSIZE; x > 0 ; x-- ) // Pulls remaining objects to one behind
    statesLeft[x] = statesLeft[x-1];   
  for ( int x = STATEBUFFERSIZE; x > 0 ; x-- ) // Pulls remaining objects to one behind
    timesLeft[x] = timesLeft[x-1];
  //Serial.println("Shift Right");
  
}

void printBufferLeft()
{
  for ( int x = 0; x<STATEBUFFERSIZE; x+=1)
  {
    Serial.print("For buffer= ");Serial.println(x);
    Serial.print("STATE: ");Serial.println(statesLeft[x]);
    Serial.print("TIME: ");Serial.println(timesLeft[x]);
  }
}

// Detects a Click on the Button
void motionSensorLeft(){
  int buttonState = digitalRead(cellLButton);
  if (buttonState != lastButtonStateL) {
    if (buttonState == HIGH) {
      // Send Message to Everyone
      spreadMovement(LX,LY, timeNow);
    }
    delay(50);
  }
  lastButtonStateL = buttonState;
}

// Lights Up the LED according to the state
void ledLeft(int state)
{
  int brightness;
  if ( state == 0 ) 
    brightness = 0;
  else if ( state == 1 )  // Safety
    brightness = 64;
  else if ( state == 2 )  // Comfort
    brightness = 127;
  else if ( state == 3 )  // On
    brightness = 255;
    
  analogWrite(cellLLed, brightness);
}
