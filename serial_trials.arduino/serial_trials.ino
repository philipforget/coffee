#define ledPin 13
#define pump_pin 13
#define boiler_pin 13

#include <SerialCommand.h>
#include <SoftwareSerial.h>

const String HELLO = "HELLO";
const String GOODBYE = "GOODBYE";
int target = 0;

SerialCommand sCmd;
SoftwareSerial ss(4,5);

// Hack lets us reset the arduino via software
void(* actual_reset) (void) = 0;

void reset(){
    ss.println("reset");
    actual_reset();
}

void boiler_on(){
    ss.println("boiler_on");
    digitalWrite(boiler_pin, HIGH);
}

void boiler_off(){
    ss.println("boiler_off");
    digitalWrite(boiler_pin, LOW);
}

void pump_on(){
    ss.println("pump_on");
    digitalWrite(pump_pin, HIGH);
}

void pump_off(){
    ss.println("pump_off");
    digitalWrite(pump_pin, LOW);
}

void set_target(){
    char *arg;

    ss.println("set_target");
    arg = sCmd.next();
    if(arg != NULL){
        target = atoi(arg);
        ss.print("setting to ");
        ss.println(target);
    }
}

void get_target(){
    ss.println("get_target");
    Serial.println(target);
}

void get_temperature(){
    ss.println("get_temperature");
    Serial.println(target + 5);
}

void unrecognized(const char *command){
    ss.print("unrecognized: ");
    ss.println(command);
}

void setup(){
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    Serial.begin(9600);
    ss.begin(9600);

    sCmd.addCommand("B0", boiler_off);
    sCmd.addCommand("B1", boiler_on);
    sCmd.addCommand("GP", get_temperature);
    sCmd.addCommand("GT", get_target);
    sCmd.addCommand("P0", pump_off);
    sCmd.addCommand("P1", pump_on);
    sCmd.addCommand("R",  reset);
    sCmd.addCommand("ST", set_target);
    sCmd.setDefaultHandler(unrecognized);

    Serial.println(HELLO);
    ss.println(HELLO);
}

void loop(){
    sCmd.readSerial();
}
