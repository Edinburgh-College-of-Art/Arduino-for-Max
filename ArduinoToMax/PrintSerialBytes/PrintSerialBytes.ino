/*
 * Print Serial
 * 
 *  Print some values to Serial and see what they look like in Proessing/MaxMSP
*/

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (uint16_t i = 65000; i <= 66000; ++i)
  {    
    Serial.write(i);
    Serial.write((i>>8));
    delay(1000);
  }
}
