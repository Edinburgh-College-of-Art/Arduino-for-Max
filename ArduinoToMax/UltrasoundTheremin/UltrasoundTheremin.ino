/*
  Ultrasound Theremin
*/
//============================================================================================
const int trigPin = 12;
const int echoPin = 13;
uint16_t distance = 1000;
//============================================================================================
void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
//============================================================================================
void loop()
{
  uint16_t newReading = getRawUltrasoundReading();
  if (newReading > 200 && newReading < 3000)
  {
    distance = newReading;
  }
  Serial.write(distance);
  Serial.write((distance >> 8));
  // Serial.print(distance) // check in Serial Plotter
  delay(30);
}
//============================================================================================
uint16_t getRawUltrasoundReading()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long pulseTime = pulseIn(echoPin, HIGH);
  return uint16_t(pulseTime);
}
//============================================================================================
