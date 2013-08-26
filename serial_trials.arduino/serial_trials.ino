#define print Serial.print
#define println Serial.println

#include <SoftwareSerial.h>

SoftwareSerial ss(12,13);

void setup(){
  Serial.begin(9600);
  println("Starting up");
}

void loop(){
  println("High");
  delay(5000);
  println("Low");
  delay(5000);
}
