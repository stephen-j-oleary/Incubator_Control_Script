
#include "TempMonitor.h"

void tempMonitor(float currentValue, float expectedValue, void (*lFunc)(), void (*hFunc)(), void (*eqFunc)()) {
  if (currentValue > expectedValue) {
    hFunc();
    return;
  }
  if (currentValue < expectedValue) {
    lFunc();
    return;
  }
  if (currentValue == expectedValue) {
    eqFunc();
    return;
  }
}

void tempMonitor(float currentValue, float minValue, float maxValue, void (*lFunc)(), void (*hFunc)(), void (*eqFunc)()) {
  if (currentValue > maxValue) {
    hFunc();
    return;
  }
  if (currentValue < minValue) {
    lFunc();
    return;
  }
  if (currentValue > minValue && currentValue < maxValue) {
    eqFunc();
    return;
  }
}
