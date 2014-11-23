#include <Wire.h>
#include "Expander.h"
#include <math.h>

void Expander::clearOutputs(){
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
  if(index >= 0 && index < _outputs_size) {
    _outputs[index] = one_or_zero;
  }
}

void Expander::send() {
  sendToPort( 0x12, _outputs_size/2 - 1, 0); //port A
  sendToPort( 0x13, _outputs_size - 1, _outputs_size/2); //por B
}

void Expander::sendToPort(int port, int start, int end){
  Wire.beginTransmission(_address);
  Wire.write(port);
  _state = 0;
  for (int i = start ; i >= end; i--) {
    _state <<= 1;
    _state |= _outputs[i];
  }
  Wire.write(_state);
  Wire.endTransmission();

}
