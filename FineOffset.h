/*
 * FineOffset - Transmit temperature and humidity using the Fine Offset
 * wireless protocol.
 *
 * Copyright (c) 2016 Björn Stenberg <bjorn@haxx.se>
 * License: MIT, see file LICENSE
 *
 */
#pragma once
#include "Arduino.h"

class FineOffset {
 public:
  FineOffset(int transmit_pin, int device_id, int repeat_count=3);
  void send(float temperature, int humidity=255);

 private:
  void send_byte(uint8_t byte);
  uint8_t crc8( uint8_t *addr, uint8_t len);
  int pin;
  int id;
  int repeat;
};
