void API(int event, int destination, int source, unsigned long t)
{
  int destX = decodeCoordX(destination);
  int destY = decodeCoordY(destination);
  int sourceX = decodeCoordX(source);
  int sourceY = decodeCoordY(source);
  Serial.println(event);
  Serial.println(t);
  if ( destX == sourceX && destY == sourceY ) // Own Message
  {
    //Serial.println("Own Message");
    if ( event == 1 )
    {
      if ( destX%2 == 0 )
        addStateLeft(3,t);
        //Serial.print(" ");
    }
  }
  else if ( (abs(sourceX-destX)<=1) && (abs(sourceY-destY)<=1) ) // Same Arduino
  {
    //Serial.println("Message to same Arduino Neighbour");
    //Serial.println("espaço2");
    //Serial.println(event);
    if ( event == 1 )
    {
      if ( destX%2 == 0 )
        addStateLeft(2,t);
        //Serial.print(" ");
      else
      {
        addStateRight(2,t);
        //Serial.print(" ");
      }
        
    }
  }
  
  // If destination even -> L
  // If destination odd -> R
}
