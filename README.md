# FineOffset
This is an Arduino library for wirelessly sending temperature and humidity using the Fine Offset protocol.

Fine Offset is a chinese manufacturer of weather stations, and their wireless protocol has become a de-facto standard
used by many others, and is understood by the Telldus line of 433 MHz receivers for computers.

This library is written for use with simple 433 MHz transmitters such as the FS1000A module.
It works on both ATmega and ATtiny cpus. 
(Just make sure you configure Arduino for the cpu clock you actually run, otherwise the protocol timing will fail.)

## Usage notes

The constructor takes two parameters: `transmit_pin` and optionally the number of transmit `repeats`
* `transmit_pin` is the cpu i/o port pin where the tx module data pin is connected
* `repeats` is the number of times each message will be sent. Default is 3.

send() takes three parameters: `device_id`, `temperature` and optional `humidity`:
* `device_id` is a value 1-255 identifying your wireless sensor to the receiver.
* `temperature` is a float. The protocol supports one decimal accuracy.
* `humidity` is the relative humidity, 0-100%. If you don't specify it, a value of 255 will be sent.

## Example code
```C
#include "FineOffset.h"

#define TX_PIN PORTB4
#define DEVICE_ID 242

FineOffset tx(TX_PIN);

void loop(void)
{
   float temp = some_sensor.read_temp();
   int hum = other_sensor.read_hum();
   
   tx.send(DEVICE_ID, temp, hum);
   delay(30000);
}
```
