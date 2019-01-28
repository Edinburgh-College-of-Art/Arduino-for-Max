/*
  Dimmer
*/

const int ledPin = 9;      // the pin that the LED is attached to

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
}

void loop() 
{
  if (Serial.available()) 
  {
    analogWrite(ledPin, Serial.read());
  }
} 
