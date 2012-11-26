#include "LM75A.h"

LM75A::LM75A(int address){
  _address = address;
}


float LM75A::get_temp(){
  return 100.1;
}
