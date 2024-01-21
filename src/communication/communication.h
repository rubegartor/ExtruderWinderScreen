#pragma once

#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x60
#define QUEUE_BUFFER_SIZE 32
#define REQUESTS_DELAY 60

class Communication {
 private:
  String requests[12] = {"reqDiameter", "reqMinPSpeed", "reqMaxPSpeed", "reqPolymer", "reqMinRead", "reqMaxRead", "reqAutostop", "reqMaxPosition", "reqMinPosition", "reqPositioned", "reqStAutoStop", "reqTemp"};
  bool requestsCompleted = false;
  uint8_t requestCompletedIndex = 0;
  long lastMillisRequests = millis();
 public:
  void init();

  void sendEvent(String eventName, String eventData);

  void handleRequests();
};