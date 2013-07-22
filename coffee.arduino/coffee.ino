char cmd0, cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7;
int past_available = 0;

void setup(){
  Serial.begin(57600);
  Serial.println("Starting up");
}


void drain_serial(){
    while(Serial.available())
      if(Serial.read() == '#')
        return;
}

void process_message(){
  // Process a fixed-frame message
  cmd0 = Serial.read();
  if(cmd0 != '%') {
    Serial.println("Message frame did not start with %");
    // Drain any remaining message parts
    return drain_serial();
  }

  cmd1 = Serial.read();
  cmd2 = Serial.read();
  cmd3 = Serial.read();
  cmd4 = Serial.read();
  cmd5 = Serial.read();
  cmd6 = Serial.read();
  cmd7 = Serial.read();

  if(cmd7 != '#'){
    Serial.println("Invalid frame ending");
    return drain_serial();
  }

  Serial.println("Received Frame");

  switch(cmd1){
    // Set
    case 'S':
      switch(cmd2){

      }
    // Get
    case 'G':
      switch(cmd2){
        case 'T':
          return get_temperature();
      }
    default:
      Serial.println("No match for message");
  }
}


void loop(){
  if(Serial.available() >= 8){
    process_message();
  }
}
