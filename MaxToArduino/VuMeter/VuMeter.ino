/*
  VuMeter
*/

int led[] = {3, 5, 6, 9, 10};

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 5; ++i)
  {
    pinMode(led[i], OUTPUT);
  }

}

void loop()
{
  if (Serial.available())
  {
    for (int i = 0; i < 5; ++i)
    {
      analogWrite(led[i], 0);
    }
    int val = Serial.read();
    for (int i = 0; i < val; ++i)
    {
      analogWrite(led[i], 100);
    }
  }
}
