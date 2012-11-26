#include "LM75A.h"

#include <Arduino.h>
#include <Wire.h>

LM75A::LM75A(int address){
  _address = address;
}


long LM75A::get_temp(){
  int c[2],                    // array for two temp bytes
      x=1;                     // counter for array (msb is send first)
  long bit_check;

  Wire.requestFrom(_address, 2);

  // Get the two bytes we asked for
  while (Wire.available()){
    c[x] = Wire.read();
    x--;
  }

  c[0] = c[0] & 224; // "forget" all bits except the 3 left bits
  c[0] = c[0] >> 5; // shift these 5 bits for the right value

  bit_check = c[1] & 256; // logical and for checking bit 8 if its 1 or 0

  if (bit_check) {
    // 2's complement for negative values
    return ((~c[1]+1)*8 + ~c[0]+1) * 0.125;  
  }
  else {
    // c[1] * 8, 'cause first bit isn't 1, but 8, second 16 and so on, a value
    // of 1 is 0.125°C
    return (c[1]*8 + c[0]) * 0.125; 
  }
}
