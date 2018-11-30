byte eventOut;
byte sourceOut;
byte destinationOut;
unsigned long eventTimeOut;

// Public Function
void spreadMovement(int inX, int inY, unsigned long t)
{
  messageToBeSent = true;
  eventOut = 1;
  sourceOut = codeCoord(inX, inY);
  eventTimeOut = t;
}

void sendMessage(int outX, int outY)
{
  int ownAddress = calcAddress(LX, LY);
  destinationOut = codeCoord(outX, outY);
  if ( outX >= 0 && outY >= 0 )
  {
    int addressOut = calcAddress(outX,outY);
    if ( ownAddress == addressOut )
      API(eventOut, destinationOut, sourceOut, eventTimeOut);
    else
    {
    }
  }
  // Wires()
}

// Auxiliary Function
int codeCoord(int x, int y)
{
  return ( y*16 ) + x;
}



int calcAddress(int x, int y)
{
  int mid = x/2;
  int result = (mid*16)+y;
  return result;
}
