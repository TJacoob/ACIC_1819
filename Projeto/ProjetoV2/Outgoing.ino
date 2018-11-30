byte eventIn;
byte sourceIn;
byte destinationIn;
unsigned long eventTimeIn;

void receiveEvent(int howMany){
 //Serial.println("Received Event"); 
 while (Wire.available() > 0){
   destinationIn = Wire.read();   
   sourceIn = Wire.read();
   eventIn = Wire.read();
   // Time
   uint32_t t;
   byte a,b,c,d;
   a = Wire.read(); b = Wire.read(); c = Wire.read(); d = Wire.read();   
   t = a; t = (t << 8) | b; t = (t << 8) | c; t = (t << 8) | d;
   eventTimeIn = t;
   // End Time
   //Serial.print("Destination: ");Serial.print(destinationIn);Serial.print(", Source: ");Serial.print(sourceIn);
   //Serial.print(", Event: ");Serial.print(eventIn);Serial.print(", Time: ");Serial.println(eventTimeIn);
   //Serial.print("Message Received from: "); Serial.print(source); Serial.print(" and Y: "); Serial.print(outY); Serial.print(" with event: "); Serial.println(event);
   //digitalWrite(LED, !b);
   //eventFilter(event,t,destination);
 }
 Serial.println("Message Received");
 if ( eventIn == 0 ) 
  handleReceived();
 else
  messageReceived = true;
}

void handleReceived(){
  API(eventIn, destinationIn, sourceIn, eventTimeIn);
}
