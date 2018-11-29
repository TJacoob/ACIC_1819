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
      //turnLightL = true;
      //movementDetectedL = t;
      movementActionL(millis());
    }
    else
    {
      //Serial.print("Current Time: ");
      //Serial.println(millis()-clockDelta);
      //Serial.print("Event Time: ");
      //Serial.println(t);
      movementActionR(millis());
    }
  }  
}
