
#ifndef PINSTATE_H
#define PINSTATE_H

struct PinState {
  // Properties
  bool boolValue;
  int integerValue;
  float floatValue;

  // Constructors
  PinState();
  PinState(bool value);
  PinState(int value);
  PinState(float value);

  // Methods
  void setBoolValue(bool value);
  void toggleBoolValue();
  void setIntegerValue(int value);
  void incrementIntValue(int value);
  void decrementIntValue(int value);
  void setFloatValue(float value);
  void incrementFloatValue(float value);
  void decrementFloatValue(float value);
};

#endif
