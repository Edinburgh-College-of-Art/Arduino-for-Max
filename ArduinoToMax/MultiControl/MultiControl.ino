/* Multi Control
 *  Output multiple values read from analog pins
*/

int controlPin[] = {A0, A1, A2, A3, A4};

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (byte i = 0; i < 5; ++i)
  {
    byte val = map(analogRead(controlPin[i]), 0, 1024, 0, 255);
    Serial.write(i);
    Serial.write(val);
  }
  delay(50);
}
