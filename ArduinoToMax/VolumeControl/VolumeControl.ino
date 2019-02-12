/*
   Volume Control

   Get Reading from analog pin and send to Max
*/

int volumePin = A0;

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
