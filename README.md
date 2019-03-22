# Arduino-for-Max
A collection of Examples for communicating between the Arduino and Cycling '74's MaxMSP


## Contents

- [MaxToArduino](#MaxToArduino)
  - [PhysicalPixel](#PhysicalPixel)
  - [Dimmer](#Dimmer)
    - [LedEnvelope](#LedEnvelope)
  - [VuMeter](#VuMeter)
- [ArduinoToMax](#ArduinoToMax)
  - [PrintSerial](#PrintSerial)
  - [PrintSerialBytes](#PrintSerialBytes)
  - [VolumeControl](#VolumeControl)
  - [MultiControl](#MultiControl)
  - [SerialCallResponse](#SerialCallResponse)
  - [UltrasoundTheremin](#UltrasoundTheremin)
- [Tools](#Tools)
 - [set_serial](#set_serial)

## Pre-amble

If this is our first outing with MaxMSP, then it may be worthwhile going through some of the [tutorials](https://docs.cycling74.com/max7/vignettes/doctutorials). It will also make your life easier if you become familiar with the various [shortcuts](https://docs.cycling74.com/max7/vignettes/keycommands) and [conventions of using Max](https://docs.cycling74.com/max7/vignettes/shortcuts)

## MaxToArduino
These examples relate to data travelling from MaxMSP to the Arduino. The main concerns here are making sure that the Arduino has enough to time to read everything in the [Serial Buffer](https://www.arduino.cc/en/serial/available) before it overflows.

### PhysicalPixel
First example is a simple on. Turn an LED on or off using your keyboard. This example is built into the Arduino IDE but included here in a tidied up and extraneous comments removed.

### Dimmer
Control the brightness of an LED with data sent from MaxMSP. This is also in the Arduino example files but there is so little going on it benefits from a re-write to trim it down. On the Arduino end, not much is going on. We simply define a pin `const int ledPin = 9;` as output `pinMode(ledPin, OUTPUT);`, begin Serial communication `Serial.begin(9600);` and wait until the there is some data to read.

```c
if (Serial.available())
{
  analogWrite(ledPin, Serial.read());
}
```

On the Max side of things, **make sure you check which serial port your Arduino is connected to by pressing the print message**. The toggle is just a slightly nicer way of opening and closing the the serial port.

#### LedEnvelope

Included as a little extra is a patch to get the envelope of an audio signal and then use that to control the brightness of your LED. Included is a little Javascript file `getMaxBufferValue.js` to get the maximum value from the buffer in order to normalise it the signal. The Up and Down float boxes dictate how quickly the signal will rise and fall. Twiddle with these to change the sensitivity of the envelope. Also included is an alternative way of getting a list of serial ports. This is essentially what is contained with the [set_serial](#set_serial) tool.

### VuMeter
This example demonstrates a very basic VU Meter. The Max patch is almost identical to the LedEnvelope example. The only exception is that the envelope is rounded to a value between 0 and 5. Envelope is sourced from the `gain~` slider, try different positions and see what happens.
On the Arduino end there are couple of interesting things happening. First we make a list of all the pins we will be using. Make sure to follow the wiring or alter the pin numbers to match your own wiring.

![Wiring Diagram](MaxToArduino/VuMeter/VuMeterWiring.jpg?raw=true "WiringDiagram")

```c++
int led[] = {3, 5, 6, 9, 10};
```

This is an [array](https://www.arduino.cc/reference/en/language/variables/data-types/array/) of integer numbers which can be referenced by an index. The index always starts at zero so `led[0]` is `3` and `led[4]` is `10`.

Benefits of using an array are the fact that we can use a placeholder for the index and shrink the amount of code we need to write. For instance, if we wanted to manually change the `pinMode` of all these pins we would need to write

```c
pinMode(3, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
```

Which becomes quite messy quite quickly. In this instance we activate all of the pins in a [for loop](https://www.arduino.cc/reference/en/language/structure/control-structure/for/) like so:

```c
for (int i = 0; i < 5; ++i)
{
  pinMode(led[i], OUTPUT);
}
```
We do something similar to turn all of the LEDs off in lines 20 - 23

```c
for (int i = 0; i < 5; ++i)
{
 analogWrite(led[i], 0);
}
```
and then only light up the number of LEDs we want in lines 24 - 28
```c
int val = Serial.read();
for (int i = 0; i < val; ++i)
{
  analogWrite(led[i], 100);
}
```
The variable `val` will set the threshold in the for loop, thus controlling the number of LEDs that light up.



## ArduinoToMax
These examples relate to sending Data from the Arduino to MaxMSP. This opens up the possibility for creating customised interfaces and any number of potentiometers, switches and sensors to begin manipulating audio.

### PrintSerial
This first example is just here to demonstrate how data flows from the Arduino to MaxMSP. A simple [for loop](https://www.arduino.cc/reference/en/language/structure/control-structure/for/) writes out values from 0 to 255 to the Max Console. Try changing the delay value on the Arduino but not in Max. The timing for data output needs to be dealt with carefully. There are more sophisticated methods for ensuring there is no mismatch, but for this purpose we will get away with it.

Also, try changing the for loop to:
```c
for (int i = 250; i < 300; ++i)
```

Can you see what happens when `i` reaches 256? How we get around that will be dealt with in the next example.
### PrintSerialBytes
This example demonstrates the constraints when sending data over serial. We can only send data byte at a time. A single byte, 8bits, is in the rang of 2^8 or 0 to 255. If we want to send larger numbers, for instance a 2 byte number (i.e. 0 to 65536) then we need to start doing some [bit shifting](https://www.arduino.cc/en/pmwiki.php?n=Reference/Bitshift). Say for instance we wanted to send the number `4101`. If we try and send that over serial, only the first 8 bits will be read, which will be the number `5`. What we can do is shift the bits and send the individual bytes separately. We can then reconstruct the number on the other side using [bitwise operators](https://www.arduino.cc/reference/en/language/structure/bitwise-operators/bitwiseand/).
```c
int num = 4101;                   // binary: 0001000000000101
int byte1 = num & 0xFF;           // binary: 0000000000000101
int byte2 = num >> 8;             // binary: 0000000000100000 or 16
int full  = (byte2 << 8) | byte1; // binary: 0001000000000101 or 4101
```
The `& 0xFF` is a mask which is an easy way of saying, "only pay attention to the first 8 bits". `0xFF` is hex code for 255 and is equivalent to `0b11111111`. The and opertaor `&` looks for matching pairs of bits.
```
0  0  1  1    byte1
0  1  0  1    byte2
----------
0  0  0  1    (byte1 & byte2)
```
If you look at the max patch, we then see the data at the other end is reconstructed. First by grouping together bytes using the `zl group` object. Then by unpacking the data and shifting the correct byte back by 8 bits and using the [OR] operator.
```
0  0  1  1    byte1
0  1  0  1    byte2
----------
0  1  1  1    (byte1 | byte2)
```

### VolumeControl
This example demonstrates the use of a [potentiometer](https://www.arduino.cc/en/tutorial/potentiometer) as a volume control.
Wiring is fairly straightforward, we are simply dividing the voltage between the analog pin `A0` on the Arduino and Ground `GND`.
![Wiring Diagram](ArduinoToMax/VolumeControl/VolumeControlWiring.png?raw=true "WiringDiagram")

One thing to be Aware of is that [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) returns a value between 0 and 1024. So, we map that value back to between 0 and 255 before sending it over serial.

### MultiControl
MultiControl demonstrates how to send multiple sensor value by using the same principles in the [PrintSerialBytes](#PrintSerialBytes) example. We send to bytes per potentiometer. The byte identifies which pin we are referencing and the second is the value from that pin. If we wanted value larger than 255 for each reading, you guessed it. We would need to send 3 bytes, 1 address byte and 2 value bytes, remembering to shift them in the correct way of course. I have left this example open, at the moment 3 readings are used to control pitch, volume and the loop point of the sample.

### SerialCallResponse
Serial Call and Response is an example included with the Arduino IDE. I have included in a tidied up version. It demonstrates how to wait until there is data ready before asking for more between the Arduino and Max. It uses the same setup as the [MultiControl](#MultiControl) example above.

### UltrasoundTheremin
As a bit of fun, included is one example of using the [HC-SR04](https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/) ultrasound distance sensor as a control of an oscillator to approach something like a theremin.
![Wiring Diagram](ArduinoToMax/UltrasoundTheremin/HC-SR04-with-Arduino.jpg?raw=true "WiringDiagram")

What you will find is that the HC-SR04 is not particularly accurate and can be quite erratic. Try averaging the data you get from it either in the Arduino or in Max before using the values returned from it.

One extra part added into the Arduino code is an area of effect in lines 19 to 22:

```c
if (newReading > 200 && newReading < 3000)
{
  distance = newReading;
}
```

What this says is that if the next reading is outside of the range 200 - 3000 then it will be ignored and old value will be kept. Try changing the range or taking it out entirely. In the Max patch, the scale object is set to be in the is range. Can you think of a way of changin the range in the Arduino and updating in Max without doing it manually?

## Tools
Included are a set of tools and scripts that I have found useful when dealing with Arduino and Max. If you have any of your own you would like to contribute, send them over.

### set_serial
set_serial can be included in a `bpatcher` object so that you can choose a serial port from a drop down menu and then activate it. A bang in the first inlet asks for the serial buffer. A toggle in the second inlet opens and closes the port.

### getMaxBufferValue.js

`getMaxBufferValue.js` can be used in a `js` object in Max. It gets the maximum value of the buffer named by a `bufname <buffername>` message and is used in the [LedEnvelope](#LedEnvelope) and [VuMeter](#VuMeter) examples.
