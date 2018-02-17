
void TX(String  tx){
 /* for (byte i = 0; i < tx.length(); i++) {
    Serial.write(tx[i]);
  }*/
  Serial.println(tx);
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
 // FinishRX = true;
}

