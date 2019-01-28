/*
   Print Serial

    Print some values to Serial and see what they look like in Proessing/MaxMSP
*/

int controlPin[] = {A0, A1};

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  for (byte i = 0; i < 2; ++i)
  {
    byte val = map(analogRead(controlPin[i]), 0, 1024, 0, 255);
    Serial.write(i);
    Serial.write(val);
  }
  delay(50);
}
