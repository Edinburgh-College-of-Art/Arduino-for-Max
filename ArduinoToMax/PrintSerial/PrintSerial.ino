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
  for (int i = 0; i < 256; ++i)
  {
    Serial.write(i);
    delay(1000);
  }
}
