uint32_t clocks[3];
int clockNum = 0;
#define CLOCKSNEEDED 2

void syncClock()
{
  clockSetup = true ;
  uint32_t ti = millis();
  uint32_t delta = 0;
  for (int i=0; i<clockNum; i++)
    delta = delta + ((ti-clocks[clockNum])/clockNum);
  Serial.print("Clock Synced, delta: "); 
  Serial.println(delta);
  clockDelta = delta;
}

void addToClocks(uint32_t t)
{
  clocks[clockNum] = t;
  clockNum += 1;
  if ( clockNum == CLOCKSNEEDED )
    syncClock();
}

void sendClock()
{
  // Send Clocks to cardinal Neighbors
  spreadClocks(LX,LY, millis());
  sendMessage(LX, LY+1);
  sendMessage(LX+1, LY);
  sendMessage(LX, LY-1);
  sendMessage(LX-1, LY);
  clockSent = true;
  Serial.println("Clocks Sent"); 
}
