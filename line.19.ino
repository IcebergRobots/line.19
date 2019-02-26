#include <EEPROM.h>

#define D0 9
#define D1 8                         //die 4 Pins fuer die Multiplexer
#define D2 11
#define D3 10


#define S1 A3                           //Input der drei Multiplexer
#define S2 A2
#define S3 A1



#define INTERPIN 7

#define INTERPIN 7                      //InterruptPin
#define PLEXEN 12

byte binPins[] = {D0, D1, D2, D3};      //die 4 Pins fuer die Multiplexer
int values[48];
int counter;

void setup() {
  Serial.begin(9600);

  counter = EEPROM.read(0) + 1;
  counter %= 41;
  EEPROM.write(0, counter);
  Serial.println("Sensor Nr.: " + String(counter));

  for (int i = 2; i <= 13; i++) {     //digitale Pins auf Input
    pinMode(i, INPUT);
  }
  pinMode(A0, OUTPUT);                 //analoge Pins auf Input
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);

  pinMode(PLEXEN, OUTPUT);
  digitalWrite(PLEXEN, LOW);


}
void loop() {
  String bin = String(counter % 16, BIN);
  int binlength = bin.length();
  bool state;

  for (int i = 0; i < 4 - binlength; i++) {
    bin = "0" + bin;
  }
  Serial.println("Controlbits: " + bin);
  delay(2000);

  for (int i = 0; i < 4; i++) {
    if (bin[i] == '0') state = LOW;
    if (bin[i] == '1') state = HIGH;
    digitalWrite(binPins[i], state);
  }

  unsigned long startT = millis() + 15000;


  while (1) {
    if (counter < 16)
      Serial.println(analogRead(S1));
    else if (counter < 32)
      Serial.println(analogRead(S2));
    else if (counter < 48)
      Serial.println(analogRead(S3));
  }
}
