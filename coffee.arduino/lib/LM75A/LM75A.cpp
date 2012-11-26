#include "LM75A.h"

#include <Wire.h>

LM75A::LM75A(int address){
  _address = address;
}


long LM75A::get_temp(){
  int c[2];                    // array for two temp bytes
  int x=1;                     // counter for array (msb is send first)
  int check;                   // var for looking if temp is + or - (Bit 11)
  long temp;                   // var contains tempdata for easy reading by human beings ;)

  Wire.requestFrom(_address, 2);     // request 2 bytes from slave device #72 

  while (Wire.available()) {   // get the two bytes
    c[x] = Wire.read();
    x--;
  }

  c[0]=c[0]&224;                           // "forget" all bits except the 3 left bits
  c[0]=c[0]>>5;                            // shift these 5 bits for the right value
  check=c[1]&256;                          // logical and for checking bit 8 if its 1 or 0
  if (check==0) {
    temp=(c[1]*8 + c[0]) * 0.125;          // c[1] * 8, 'cause first bit isn't 1, but 8, second 16 and so on, a value of 1 is 0.125°C
  }
  else {
    temp=((~c[1]+1)*8 + ~c[0]+1) * 0.125;  // 2's complement for -
  }

  return temp;
}
