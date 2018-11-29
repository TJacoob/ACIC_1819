int clocks[3];
int clockNum = 0;
#define CLOCKSNEEDED 3


void syncClock()
{
  clockSetup = true ;
  Serial.println("Clock Synced"); 
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
  sendComms(0, LX, LY, LX, LY+1);
  sendComms(0, LX, LY, LX+1, LY);
  sendComms(0, LX, LY, LX, LY-1);
  sendComms(0, LX, LY, LX-1, LY);
  clockSent = true;
  Serial.println("Clocks Sent"); 
}
