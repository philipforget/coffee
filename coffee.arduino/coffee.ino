#include <LM75A.h>

// Max serial speed between arduino and ipod touch
# define SERIAL_SPEED 19200
# define BCAST_INTERVAL 500

long b_previous_m = 0;
LM75A lm(100);

void setup(){
  Serial.begin(SERIAL_SPEED);
  Serial.println("Starting up");
}


float get_temp(){
  return lm.get_temp();
}


void broadcast_temperature(){
  unsigned long current_m = millis();

  if( current_m - b_previous_m > BCAST_INTERVAL){
    b_previous_m = current_m;
    Serial.println(get_temp());
  }
}


void loop(){
  broadcast_temperature();
}
