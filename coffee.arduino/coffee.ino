#define HEAD 0x02
#define STOP 0x03
byte i, val, code[6], checksum, bytesread, tempbyte;

void setup() {
  Serial.begin(9600); 
  Serial.println("Starting up");
}

void loop () {
  i = 0;
  checksum = 0;
  bytesread = 0;
  tempbyte = 0;

  if (Serial.available()) {
    // Check for header byte
    val = Serial.read();
    Serial.println(val);
    if (val == 2) {
      // read 10 digit code + 2 digit checksum
      while (bytesread < 12) {
        if (Serial.available()) { 
          val = Serial.read();
          // if header or stop bytes before the 10 digit reading 

          if((val == 0x0D)||(val == 0x0A)||(val == 0x03)||(val == 0x02)) { 
            break;
          }

          // Do Ascii/Hex conversion:
          if ((val >= '0') && (val <= '9')) {
            val = val - '0';
          } else if ((val >= 'A') && (val <= 'F')) {
            val = 10 + val - 'A';
          }

          // Every two hex-digits, add byte to code:
          if (bytesread & 1 == 1) {
            // make some space for this hex-digit by
            // shifting the previous hex-digit with 4 bits to the left:
            code[bytesread >> 1] = (val | (tempbyte << 4));

            if (bytesread >> 1 != 5) {                // If we're at the checksum byte,
              checksum ^= code[bytesread >> 1];       // Calculate the checksum... (XOR)
            };
          } else {
            tempbyte = val;                           // Store the first hex digit first...
          };

          bytesread++;                                // ready to read next digit
        } 
      } 

      // Output to Serial:
      if (bytesread == 12) {
        Serial.print("5-byte code: ");
        for (i=0; i<5; i++) {
          if (code[i] < 16) Serial.print("0");
          Serial.print(code[i], HEX);
          Serial.print(" ");
        }
        Serial.println();

        Serial.print("Checksum: ");
        Serial.print(code[5], HEX);
        Serial.println(code[5] == checksum ? " -- passed." : " -- error.");
        Serial.println();
      }

      bytesread = 0;
    }
  }
}
