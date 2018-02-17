#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
float dataRec[2];
char ch = 0;
byte numget ;
String inData;
float datarelay1 = 0;
float datarelay2 = 0;
float datarelay3 = 0;
float datarelay4 = 0;
int Son1, Soff1 , Son2, Soff2 , Son3, Soff3, Son4, Soff4;
String  Ton1 ,  Toff1 , Ton2 ,  Toff2, Ton3 ,  Toff3, Ton4 ,  Toff4;
#define sendMega D2
// Config Firebase
#define FIREBASE_HOST "test-ce9c3.firebaseio.com"
#define FIREBASE_AUTH "qQj5gkADsPzuY4fxeIsAtW1WxTPNbu4SmO5WMedX"

// Config connect WiFi
#define WIFI_SSID "kang"
#define WIFI_PASSWORD "pumai1234"


void setup() {
  pinMode(D2, OUTPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(57600);
  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void SET_Firbase() {
  // append a new value to /temperature
  Firebase.setFloat("temperature", dataRec[0]);
  if (Firebase.failed()) {
    return;
  }
  // append a new value to /temperature
  Firebase.setFloat("humidity", dataRec[1]);
  if (Firebase.failed()) {
    return;
  }
  delay(500);
}
void Get_Firbase() {
  numget = Firebase.getInt("number");
}
void GetFrieRealy_1() {
  Son1 = Firebase.getInt("Automatic/CH1/statusOff");
  Soff1 = Firebase.getInt("Automatic/CH1/statusOn");
  Ton1 = Firebase.getString("Automatic/CH1/timeOff");
  Toff1 = Firebase.getString("Automatic/CH1/timeOn");
}
void GetFrieRealy_2() {
  Son2 = Firebase.getInt("Automatic/CH2/statusOff");
  Soff2 = Firebase.getInt("Automatic/CH2/statusOn");
  Ton2 = Firebase.getString("Automatic/CH2/timeOff");
  Toff2 = Firebase.getString("Automatic/CH2/timeOn");
}
void GetFrieRealy_3() {
  Son3 = Firebase.getInt("Automatic/CH3/statusOff");
  Soff3 = Firebase.getInt("Automatic/CH3/statusOn");
  Ton3 = Firebase.getString("Automatic/CH3/timeOff");
  Toff3 = Firebase.getString("Automatic/CH3/timeOn");
}
void GetFrieRealy_4() {
  Son4 = Firebase.getInt("Automatic/CH4/statusOff");
  Soff4 = Firebase.getInt("Automatic/CH4/statusOn");
  Ton4 = Firebase.getString("Automatic/CH4/timeOff");
  Toff4 = Firebase.getString("Automatic/CH4/timeOn");
}
void TXmega1() {
  String SUMstatus = "W" + String(Son1) + "," + String( Soff1) + Ton1 + "," + Toff1;
  TX(SUMstatus);
}
void TXmega2() {
  String SUMstatus = "X" + String(Son2) + "," + String( Soff2) + Ton2 + "," + Toff2;
  TX(SUMstatus);
}
void TXmega3() {
  String SUMstatus = "Y" + String(Son3) + "," + String( Soff3) + Ton3 + "," + Toff3;
  TX(SUMstatus);
}
void TXmega4() {
  String SUMstatus = "Z" + String(Son4) + "," + String( Soff4) + Ton4 + "," + Toff4 ;
  TX(SUMstatus);
}
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void loop() {
  if (Firebase.getInt("Automatic/updateStatus") == 0) {
   // int relay1 = Firebase.getInt("Device/Relay/CH1");
    int relay2 = Firebase.getInt("Device/Relay/CH1");
  //  int relay3 = Firebase.getInt("Device/Relay/CH3");
  //  int relay4 = Firebase.getInt("Device/Relay/CH4");
    // if send to mega
    digitalWrite(D4,relay2);
    //sendTomega(1,String(relay2)); //relaycontrol 2 3
    // delay(360);
    sendTomega(1, "");
    while (Serial.available() > 0)
    {
      char recieved = Serial.read();
      inData += recieved;
      if (recieved == '\n')
      {
        datarelay1 = getValue(inData, '=', 0).toFloat();
        datarelay2 = getValue(inData, '=', 1).toFloat();
        datarelay3 = getValue(inData, '=', 2).toFloat();
        datarelay4 = getValue(inData, '=', 3).toFloat();
         // Serial.print(dataFirebase);
        //  Serial.print(" ");
        //  Serial.print(datarelay2);
        inData = "";
      }
    }
    Firebase.set("Device/Temp/Node1", datarelay1);
    Firebase.set("Device/Temp/Node2", datarelay2);
    Firebase.set("Device/Humidity/Node1", datarelay3);
    Firebase.set("Device/Humidity/Node2", datarelay4);
   // Serial.println(dataFirebase);

  } else {
    //Serial.println("update");
    int statusOffRelay1 = Firebase.getInt("Automatic/CH1/statusOff");
    int statusOnRelay1 = Firebase.getInt("Automatic/CH1/statusOn");
    int statusOffRelay2 = Firebase.getInt("Automatic/CH2/statusOff");
    int statusOnRelay2 = Firebase.getInt("Automatic/CH2/statusOn");
    int statusOffRelay3 = Firebase.getInt("Automatic/CH3/statusOff");
    int statusOnRelay3 = Firebase.getInt("Automatic/CH3/statusOn");
    int statusOffRelay4 = Firebase.getInt("Automatic/CH4/statusOff");
    int statusOnRelay4 = Firebase.getInt("Automatic/CH4/statusOn");
    String timeOff1 = Firebase.getString("Automatic/CH1/timeOff");
    String timeOn1 = Firebase.getString("Automatic/CH1/timeOn");
    String timeOff2 = Firebase.getString("Automatic/CH2/timeOff");
    String timeOn2 = Firebase.getString("Automatic/CH2/timeOn");
    String timeOff3 = Firebase.getString("Automatic/CH3/timeOff");
    String timeOn3 = Firebase.getString("Automatic/CH3/timeOn");
    String timeOff4 = Firebase.getString("Automatic/CH4/timeOff");
    String timeOn4 = Firebase.getString("Automatic/CH4/timeOn");

    String HumiHigh = Firebase.getString("Automatic/limit/HumiHigh");
    String HumiLow = Firebase.getString("Automatic/limit/HumiLow");
    String tempHigh = Firebase.getString("Automatic/limit/tempHigh");
    String tempLow = Firebase.getString("Automatic/limit/tempLow");

    sendTomega(0, String(statusOffRelay1) + "=" + String(statusOnRelay1) + "=" + timeOn1 + "=" + timeOff1);
    delay(1000);
    sendTomega(0, String(statusOffRelay2) + "=" + String(statusOnRelay2) + "=" + timeOn2 + "=" + timeOff2);
    delay(1000);
    sendTomega(0, String(statusOffRelay3) + "=" + String(statusOnRelay3) + "=" + timeOn3 + "=" + timeOff3);
    delay(1000);
    sendTomega(0, String(statusOffRelay4) + "=" + String(statusOnRelay4) + "=" + tempLow + "=" + timeOff4);
    delay(1000);
    sendTomega(0, tempHigh + "=" + tempLow + "=" + HumiHigh + "=" + HumiLow);
    delay(1000);
    //sendTomega(0, String(statusOffRelay1) + "=" + String(statusOnRelay1) + "=" + timeOn1 + "=" + timeOff1 + "=" + String(statusOffRelay2) + "=" + String(statusOnRelay2) + "=" + timeOn2 + "=" + timeOff2 + "=" +
    //String(statusOffRelay3) + "=" + String(statusOnRelay3) + "=" + timeOn3 + "=" + timeOff3 + "=" + String(statusOffRelay4) + "=" + String(statusOnRelay4) + "=" + timeOn4 + "=" + timeOff4);
    Firebase.set("Automatic/updateStatus", 0); //update success
  }
}
void sendTomega(int status__, String message) {
  digitalWrite(sendMega, status__);
  TX(message);
}

