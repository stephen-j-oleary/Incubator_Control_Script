
#ifndef TEMPMONITOR_H
#define TEMPMONITOR_H

void tempMonitor(float currentValue, float expectedValue, void (*lFunc)(), void (*hFunc)(), void (*eqFunc)());
void tempMonitor(float currentValue, float minValue, float maxValue, void (*lFunc)(), void (*hFunc)(), void (*eqFunc)());

#endif
