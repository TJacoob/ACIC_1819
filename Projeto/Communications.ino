int addressIn;
int addressOut;


void receiveEvent(int howMany){
 Serial.println("ReceivedEvent"); 
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
   Serial.print("Destination: ");Serial.println(destination);Serial.print("Source: ");Serial.println(source);
   Serial.print("Event: ");Serial.println(event);Serial.print("Time: ");Serial.println(t);
   //digitalWrite(LED, !b);
   if ( event == 0 && (!clockSetup) )
    addToClocks(t);
 }
 Serial.println("Received Message"); 
}

void sendComms(int e, int inX, int inY, int outX, int outY)
{
  Serial.println("Sending Message");
  if ( outX >= 0 && outY >=0 )
  {
    addressIn = calcAddress(inX, inY);
    addressOut = calcAddress(outX, outY);
    Serial.print("Own Address: ");
    Serial.println(addressIn);
    Serial.print("Out Address: ");
    Serial.println(addressOut);
  }
  else
  Serial.println("Invalid Addresses");
  
  Wire.beginTransmission(addressOut);
  byte destination = addressOut;
  byte source = addressIn;
  byte event = e;
  // Time
  uint32_t bigNum = millis()-clockDelta;
  byte t[4];
   
  t[0] = (bigNum >> 24) & 0xFF;
  t[1] = (bigNum >> 16) & 0xFF;
  t[2] = (bigNum >> 8) & 0xFF;
  t[3] = bigNum & 0xFF;
  // End Time
  Wire.write(destination);
  Wire.write(source);
  Wire.write(event);
  Wire.write(t,4);
  //Serial.println("MiddleOut");
  Wire.endTransmission(); 
  Serial.println("Sent Message");
}

int calcAddress(int x, int y)
{
  int mid = x/2;
  int result = (mid*16)+y;
  return result;
}
