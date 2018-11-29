void eventFilter(int event, uint32_t t, int dest)
{
  if ( event == 0 && (!clockSetup) )
  {
    addToClocks(t);
    Serial.println("Clock Received");
  }
  if ( event == 1 )
  {
    if( isLeftSide(dest) )
    {
      //Serial.println("Oh yea");
      //turnLightL = true;
      //movementDetectedL = t;
      movementActionL(t);
    }
    else
    {
      //Serial.println("Shiim");
      //Serial.print("Current Time: ");
      //Serial.println(millis()-clockDelta);
      //Serial.print("Event Time: ");
      //Serial.println(t);
      movementActionR(t);
    }
  }  
}
