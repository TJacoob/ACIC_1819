void API(int event, int destination, int source, unsigned long t)
{
  int destX = decodeCoordX(destination);
  int destY = decodeCoordY(destination);
  int sourceX = decodeCoordX(source);
  int sourceY = decodeCoordY(source);
  Serial.print("API CALL, Event: ");Serial.print(event);
  Serial.print(", Time: "); Serial.println(t);
  Serial.print("DestX: ");Serial.println(destX);
  Serial.print("DestY: ");Serial.println(destY);
  Serial.print("SourceX: ");Serial.println(sourceX);
  Serial.print("SourceY: ");Serial.println(sourceY);
  
  // Esquerda
  if ( destX % 2 == 0 )
  {
    if ( sourceX == LX && sourceY == LY ) // Fui eu
    {
      if ( event == 0 )
        return;
      if ( event == 1 )
      {
        addStateLeft(3,t);
        return; 
      }
    }
    else  // Foi outro
    {
      if ( event == 0 )
      {
        addToClocks(t);
        Serial.println("Clock Received");
        return;
      }
      if ( event == 1 )
      {
        addStateLeft(2,t);
        return;
      }
    }
  }
  else  // Direita
  {
    if ( sourceX == RX && sourceY == RY ) // Fui eu
    {
      if ( event == 0 )
        return;
      if ( event == 1 )
      {
        addStateRight(3,t);
        return;
      }
    }
    else  // Foi outro
    {
      if ( event == 0 )
      {
        addToClocks(t);
        Serial.println("Clock Received");
        return;
      }
      if ( event == 1 )
      {
        addStateRight(2,t);
        return;
      }
    }
  }
}
