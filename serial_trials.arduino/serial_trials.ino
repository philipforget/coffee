#define print Serial.print
#define println Serial.println

void setup(){
  Serial.begin(9600);
  println("Starting up");
}

void loop(){
  println("Hello there python, this is arduino");

  delay(1000);
}
