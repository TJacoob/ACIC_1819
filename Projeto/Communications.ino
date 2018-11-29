byte event;
int sourceX;
int sourceY;
uint32_t eventTime;

void setUpMessage(int e, int inX, int inY)
{
  //destination = codeCoord(outX,outY);
  //source = codeCoord(inX,inY);
  sourceX = inX;
  sourceY = inY;
  event = e;
  eventTime = millis();
}

// Send Message to (X,Y) Cell
void sendComms(int outX, int outY)
{
  int addressIn;
  int addressOut;
  byte source = codeCoord(sourceX, sourceY);
  byte destination = codeCoord(outX, outY);
  
  if ( outX >= 0 && outY >=0 )
  {
    addressIn = calcAddress(sourceX, sourceY);
    addressOut = calcAddress(outX, outY);
  }
  else
    return;

  // Own Actions Filter
  if ( (addressIn == addressOut) && (source != destination) )
    eventFilter(event,millis(),destination);
  
  Wire.beginTransmission(addressOut);
  // Time
  byte t[4];
   
  t[0] = (eventTime >> 24) & 0xFF;
  t[1] = (eventTime >> 16) & 0xFF;
  t[2] = (eventTime >> 8) & 0xFF;
  t[3] = eventTime & 0xFF;
  // End Time
  Wire.write(destination);
  Wire.write(source);
  Wire.write(event);
  Wire.write(t,4);
  //Serial.println("MiddleOut");
  Wire.endTransmission(); 
  Serial.print("Message Sent to X: "); Serial.print(outX); Serial.print(" and Y: "); Serial.print(outY); Serial.print(" with event: "); Serial.println(event);
  //Serial.print("Destination: "); Serial.println(addressOut);//Serial.print(", Source: "); Serial.println(source);
  //delay(10);
}

// Loops every Neighbor and send the setup message
int sendToAll()
{
  for ( int x=-1; x<=1; x += 1 )
  {
    for ( int y=-1; y<=1; y += 1 )
      sendComms(RX+x, RY+y);
  }
}

void receiveEvent(int howMany){
 //Serial.println("ReceivedEvent"); 
 while (Wire.available() > 0){
   byte destination = Wire.read();   
   byte source = Wire.read();
   byte event = Wire.read();
   // Time
   uint32_t t;
   byte a,b,c,d;
   a = Wire.read(); b = Wire.read(); c = Wire.read(); d = Wire.read();   
   t = a; t = (t << 8) | b; t = (t << 8) | c; t = (t << 8) | d;
   // End Time
   Serial.print("Destination: ");Serial.print(destination);Serial.print(", Source: ");Serial.print(source);
   Serial.print(", Event: ");Serial.print(event);Serial.print(", Time: ");Serial.println(t);
   //Serial.print("Message Received from: "); Serial.print(source); Serial.print(" and Y: "); Serial.print(outY); Serial.print(" with event: "); Serial.println(event);
   //digitalWrite(LED, !b);
   eventFilter(event,t,destination);
    
 }
 //Serial.println("Received Message"); 
}


int calcAddress(int x, int y)
{
  int mid = x/2;
  int result = (mid*16)+y;
  return result;
}

int codeCoord(int x, int y)
{
  return ( y*16 ) + x;
}

boolean isLeftSide(int d)
{
  return (d%2 == 0);
}
