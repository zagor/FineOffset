#include <FineOffset.h>

FineOffset::FineOffset(int transmit_pin, int device_id, int repeat_count)
{
  pin = transmit_pin;
  id = device_id;
  repeat = repeat_count;
  pinMode(pin, OUTPUT);
}

void FineOffset::send_byte(uint8_t byte)
{
  for(int i=0; i<8; i++) {
    int delay = 1500;
    digitalWrite(pin, HIGH);
    if (byte & 0x80)
      delay = 500;
    delayMicroseconds(delay);
    digitalWrite(pin, LOW);
    delayMicroseconds(1000);
    byte <<= 1;
  }
}

void FineOffset::send(float temperature, int humidity)
{
  uint8_t crc;
  uint8_t bytes[4];
  int inttemp = round(abs(temperature * 10));
  int sign = (temperature < 0) ? 1 : 0;

  uint32_t data =
    ((long)id << 20) |
    ((long)sign << 19) |
    ((long)inttemp << 8) |
    (long)humidity;

  for (int i=0, mask=24; i<4; i++, mask-=8)
    bytes[i] = (data >> mask) & 0xff;

  crc = crc8(bytes, 4);

  for (int r=0; r<repeat; r++) {
    send_byte(0xff); // preamble
    for (int i=0; i<4; i++)
      send_byte(bytes[i]);
    send_byte(crc);
    if (repeat > 1)
      delay(10);
  }
}

uint8_t FineOffset::crc8( uint8_t *addr, uint8_t len)
{
  uint8_t crc = 0;

  // Indicated changes are from reference CRC-8 function in OneWire library
  while (len--) {
    uint8_t inbyte = *addr++;
    for (uint8_t i = 8; i; i--) {
      uint8_t mix = (crc ^ inbyte) & 0x80; // changed from & 0x01
      crc <<= 1; // changed from right shift
      if (mix) crc ^= 0x31;// changed from 0x8C;
      inbyte <<= 1; // changed from right shift
    }
  }
  return crc;
}
