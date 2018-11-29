void eventFilter(int event, uint32_t t, int dest, int source)
{
  if ( event == 0 && (!clockSetup) )
  {
    addToClocks(t);
    Serial.println("Clock Received");
  }
  if ( event == 1 )
  {
    Serial.println(dest);Serial.println(source);
    if( isLeftSide(dest) )
    {
      if ( dest == source )
        movementActionL(t,3);
      else
      {
        Serial.println("here");
        movementActionL(t,2);
      }
        
    }
    else
    {
      if ( dest == source )
        movementActionR(t,3);
      else
        movementActionR(t,2);
    }
  }  
}
