/*
   Serial Call and Response
   Send a message over Serial and wait for confirmation that it has been recieved before continuing communication
*/
//============================================================================================
int inByte = 0;         // incoming serial byte
int controlPin[] = {A0, A1, A2, A3, A4};
//============================================================================================
void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  establishContact();  // send a byte to establish contact until receiver responds
}
//============================================================================================
void loop()
{
  if (Serial.available() > 0)
  {
    for (byte i = 0; i < 5; ++i)
    {
      byte val = map(analogRead(controlPin[i]), 0, 1024, 0, 255);      
      Serial.write(i);
      Serial.write(val);      
    }
  }
}
//============================================================================================
void establishContact()
{
  while (Serial.available() <= 0)
  {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}
//============================================================================================
