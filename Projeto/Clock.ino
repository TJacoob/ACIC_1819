int clocks[3];
int clockNum = 0;
#define CLOCKSNEEDED 1

void syncClock()
{
  clockSetup = true ;
  int ti = millis();
  int delta = 0;
  for (int i=0; i<clockNum; i++)
    delta = delta + ((ti-clocks[clockNum])/clockNum);
  Serial.print("Clock Synced, delta: "); 
  Serial.println(delta);
  clockDelta = delta;
}

void addToClocks(int t)
{
  clocks[clockNum] = t;
  clockNum += 1;
  if ( clockNum == CLOCKSNEEDED )
    syncClock();
}

void sendClock()
{
  // Send Clocks to cardinal Neighbors
  setUpMessage(0, LX, LY); sendComms(LX, LY+1);
  setUpMessage(0, LX, LY); sendComms(LX+2, LY);
  setUpMessage(0, LX, LY); sendComms(LX, LY-1);
  setUpMessage(0, LX, LY); sendComms(LX-1, LY);
  clockSent = true;
  Serial.println("Clocks Sent"); 
}
