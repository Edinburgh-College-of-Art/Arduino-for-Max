/*
   Print Serial

    Print some values to Serial and see what they look like in Proessing/MaxMSP
*/

int volumePin = A1;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  byte volume = map(analogRead(volumePin), 0, 1024, 0, 255);
  Serial.write(volume);
  delay(50);
}
