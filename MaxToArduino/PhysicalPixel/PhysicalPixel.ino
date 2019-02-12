/*
  Physical Pixel

  An example of using the Arduino board to receive data from the computer. In
  this case, the Arduino boards turns on an LED when it receives the character
  'H', and turns off the LED when it receives the character 'L'.

  The data can be sent from the Arduino Serial Monitor, or another program like
  Processing (see code below), Flash (via a serial-net proxy), PD, or Max/MSP.

  The circuit:
  - LED connected from digital pin 13 to ground

  created 2006
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe and Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/PhysicalPixel
*/
//============================================================================================
const int ledPin = 13; // the pin that the LED is attached to
//============================================================================================
void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
//============================================================================================
void loop() 
{
  if (Serial.available() > 0) 
  {
    int incomingByte = Serial.read();
    if (incomingByte == 'H') 
      digitalWrite(ledPin, HIGH);
    if (incomingByte == 'L') 
      digitalWrite(ledPin, LOW);
  }
}
