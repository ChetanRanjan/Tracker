#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
  defining the baudrate and receiver and transmitter pins
*/
static const int RXPin = 10, TXPin = 11;
static const int gsmRXPin = 2, gsmTXPin = 3;
static const   GPSBaud = 9600;
static const String masterMobileNumber = "+919513066050";
String myContacts[] = {"+919513066050", "+919845239908", "+919845638636"};

// The TinyGPS++ object
TinyGPSPlus gps;
  
// The serial connection to the GPS device
SoftwareSerial serialGPS(RXPin, TXPin);
SoftwareSerial serialGSM(gsmTXPin, gsmRXPin);

void setup() {
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  serialGPS.begin(GPSBaud);
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  
  //Setting up the GPS Setup
  
  Serial.println(sendATCommands("AT"));
  String res = sendATCommands("AT+CREG?");
  Serial.println("GSM Status "+ res );
  //waitng untill the sim is initializes
  // while(!sendATCommands("AT+CREG?").equalsIgnoreCase("ok")){
  //   Serial.println("Initialising GSM . . . ");
  //   delay(500);
  // }
  // //configuting GSM to receive the 
  // sendATCommands("AT+CMGF=1");
}

String getDetails(){
  String currentData = "";
  while(Serial.available()){
    currentData = serialGSM.readString();
    Serial.println(currentData);
  }
  return currentData;
}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (serialGPS.available() > 0)
    if (gps.encode(serialGPS.read()))
      displayInfo();
      receiveSMS();
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.print("No of satellites connected ");
    Serial.println(gps.satellites.value());
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo() {
  Serial.print(F("Location: ")); 
  Serial.println(gps.location.isValid());
  Serial.println("this is from displayInfo() outside if loop");
  Serial.println(gps.satellites.value());
  Serial.print("Altitute at ");
  Serial.println(gps.altitude.kilometers());
  if (gps.location.isValid()) {
    digitalWrite(12, HIGH);
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print(F("INVALID"));
    digitalWrite(12, LOW);
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid()) {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  } else {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}

//gsm methods
String sendATCommands(String command){
  String gsmATResp = "";
  serialGSM.println(command);
  delay(500);
  while(serialGSM.available()){
    if(command.indexOf("CMGS") > 0){
      while(gsmATResp.indexOf("gsmATResp")<0){
        gsmATResp = serialGSM.readString();
      }
      delay(500);
      return gsmATResp;
    }
    gsmATResp = serialGSM.readString();
    delay(500);
  }
  return gsmATResp;
}

void updateSerial(){
  delay(500);
  while(Serial.available()){
    serialGSM.write(Serial.read());
  }
  while(serialGSM.available()){
    Serial.write(serialGSM.read());
  }
}

void receiveSMS(){
  sendATCommands("AT+CMGF=1");
  sendATCommands("AT+CNMI=1,2,0,0,0");
  getDetails();
}
