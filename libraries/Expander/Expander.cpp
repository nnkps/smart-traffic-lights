#include <Wire.h>
#include <Expander.h>
#include <math.h>

void Expander::clearOutputs() {
  for(int i = 0; i < _outputs_size; i++) {
    _outputs[i] = false;
  }
}

Expander::Expander(int address) {
  _address = address;
  clearOutputs();
}

void Expander::test() {
  for(int i = 0; i < _outputs_size; i++) {
    _outputs[i] = true;
  }
}

void Expander::init() {
  Wire.beginTransmission(_address);
  Wire.write(0x00); // init IO port A
  Wire.write(0x00); // ustawienie na output
  Wire.endTransmission();

  Wire.beginTransmission(_address);
  Wire.write(0x01); // init IO port B
  Wire.write(0x00); // ustawienie na output
  Wire.endTransmission();
}

void Expander::setSingleOutput(int index, bool one_or_zero) {
  if(index >= 0 && index < 16) {
    _outputs[index] = one_or_zero;
  }
}

void Expander::send() {
  Wire.beginTransmission(_address);
  Wire.write(0x12); // port A
  int state = 0;
  for (int i = 0 ; i < _outputs_size/2; i++) {
    if (_outputs[i]) state += pow(2, i);
  }
  Wire.write(state);
  Wire.endTransmission();

  Wire.beginTransmission(_address);
  Wire.write(0x13); // port B
  state = 0;
  for (int i = _outputs_size/2 ; i < _outputs_size; i++) {
    if (_outputs[i]) state += pow(2, i - _outputs_size/2);
  }
  Wire.write(state);
  Wire.endTransmission();
  clearOutputs();
}
