#define print Serial.print
#define println Serial.println

int intValue = 258;
// 258 in hex is 0x102
// 258 in bin is 100000010

void setup(){
  Serial.begin(9600);
  println("Starting up");
}

void loop(){
  int loWord, hiWord;
  byte loByte, hiByte;

  hiByte = highByte(intValue);
  loByte = lowByte(intValue);

  print("decimal: ");
  println(intValue, DEC);
  print("hex    : ");
  println(intValue, HEX);
  println();

  print("low    : ");
  println(loByte, DEC);
  print("high   : ");
  println(hiByte, DEC);

  delay(10000);
}
