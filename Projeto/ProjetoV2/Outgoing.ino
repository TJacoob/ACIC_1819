byte eventOut;
byte sourceOut;
byte destinationOut;
unsigned long eventTimeOut;

void spreadClocks(int inX, int inY, unsigned long t)
{
  //messageToBeSent = true;
  eventOut = 0;
  sourceOut = codeCoord(inX, inY);
  eventTimeOut = t;
}

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
      Wire.beginTransmission(addressOut);
      // Time
      byte t[4];
       
      t[0] = (eventTimeOut >> 24) & 0xFF;
      t[1] = (eventTimeOut >> 16) & 0xFF;
      t[2] = (eventTimeOut >> 8) & 0xFF;
      t[3] = eventTimeOut & 0xFF;
      // End Time
      Wire.write(destinationOut);
      Wire.write(sourceOut);
      Wire.write(eventOut);
      Wire.write(t,4);
      //Serial.println("MiddleOut");
      Wire.endTransmission(); 
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
