# FineOffset
This is an Arduino library for wirelessly sending temperature and humidity using the Fine Offset protocol.

Fine Offset is a chinese manufacturer of weather stations, and their wireless protocol has become a de-facto standard
used by many others, and is understood by the Telldus line of 433 MHz receivers for computers.

This library is written for use with simple 433 MHz transmitters such as the FS1000A module.
It works on both ATmega and ATtiny cpus. 
(Just make sure you configure Arduino for the cpu clock you actually run, otherwise the protocol timing will fail.)

## Usage notes

The constructor takes three paramters: Transmit pin, device id, and optionally then number of transmit repeats (default 3).

send() takes two parameters: Temperature and optional humidity. If you don't specify humidity, 255 will be sent.

## Example code
```C
#include "FineOffset.h"

#define TX_PIN 4
#define DEVICE_ID 242

FineOffset tx(TX_PIN, DEVICE_ID);

void loop(void)
{
   float temp = some_sensor.read_temp();
   int hum = other_sensor.read_hum();
   
   tx.send(temp, hum);
   delay(30000);
}
```
