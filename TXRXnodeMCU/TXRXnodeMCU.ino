void setup() {
  Serial.begin(9600);
}
float dataRec[1];
int recvie = 0;
char ch = 0;
float x1 = 23.4, x2 = 22.7;
String c = String(x1) + "," + String(x2); // "23.2,25.2"
void loop() {
  TX(c);
  //  RX_to_Float();
}

void TX(String  tx) {
  delay(1000);
  for (byte i = 0; i < tx.length(); i++) {
    Serial.write(tx[i]);
  }
  Serial.println();
}

char RX() {
  if (Serial.available()) {
    ch = Serial.read();
    return ch;
  }
}
void RX_to_Float() {
  RX();
  int i = 0;
  String s[2];
  while (ch != '\0') {
    if (ch != ',') {
      s[i] += ch;
    }
    else
      i++;
    ch = RX();
  }
  delay(1000);
  for (int i = 0; i < 2; i++) {
    dataRec[i] =  s[i].toFloat(); //convers array string to array float
    Serial.println(dataRec[i]);
  }
  Serial.println();
}






