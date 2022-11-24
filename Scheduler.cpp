
#include "Scheduler.h"

#include <Arduino.h>
#include <string>

void Scheduler::every(unsigned long interval, std::string id, void (*f)()) {
  unsigned long ms = millis();
  unsigned long prevMS = previousCalls[id] | 0;
  if (ms - prevMS >= interval) {
    previousCalls[id] = ms;
    f();
  }
}
