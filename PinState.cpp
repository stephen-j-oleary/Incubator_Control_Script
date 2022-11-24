
#include "PinState.h"

// Constructors
PinState::PinState() : boolValue(), integerValue() {}
PinState::PinState(bool value) : boolValue(value) {}
PinState::PinState(int value) : integerValue(value) {}
PinState::PinState(float value) : floatValue(value) {}

// Methods
void PinState::setBoolValue(bool value) {
  boolValue = value;
}
void PinState::toggleBoolValue() {
  boolValue = !boolValue;
}
void PinState::setIntegerValue(int value) {
  integerValue = value;
}
void PinState::incrementIntValue(int value = 1) {
  integerValue += value;
}
void PinState::decrementIntValue(int value = 1) {
  integerValue -= value;
}
void PinState::setFloatValue(float value) {
  floatValue = value;
}
void PinState::incrementFloatValue(float value = 1) {
  floatValue += value;
}
void PinState::decrementFloatValue(float value = 1) {
  floatValue -= value;
}
