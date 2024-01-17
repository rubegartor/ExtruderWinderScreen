#pragma once

#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x60
#define QEUE_BUFFER_SIZE 32

class Communication {
 public:
  void init();

  void sendEvent(String eventName, String eventData);
};