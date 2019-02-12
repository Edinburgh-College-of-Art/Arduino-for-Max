/*
 * Print Serial Bytes
 * 
 *  Print some values to Serial and see what they look like in Proessing/MaxMSP
 *  Illustrating bit shifting to  send larger numbers
*/

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (uint16_t i = 255; i <= 300; ++i)
  {    
    Serial.write(i);
    Serial.write((i>>8));
    delay(1000);
  }
}
