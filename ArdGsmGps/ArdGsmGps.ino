#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int gpsRX_PIN = 6, gpsTX_PIN = 5, gsmRX_PIN = 3, gsmTX_PIN = 2;
float iLat, iLng;

//Initialising tinyGPS module
TinyGPSPlus gps;
SoftwareSerial sgps(gpsRX_PIN, gpsTX_PIN);
SoftwareSerial sgsm(gsmRX_PIN, gsmTX_PIN);
.

void sendCommand(String command){
  Serial.println(command);
  delay(1000);
}


void setup() {
  Serial.begin(9600);
  Serial.println("Serial communication Initialized");
  delay(1000);
  sgps.begin(9600);
  sgsm.begin(9600);
  sendCommand("$PMTK220,100*2F");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(sgps.available());
  sgps.listen();
  
  while(sgps.available()){
    int gpsEncodedValue = sgps.read();
    Serial.write(sgps.read());
    Serial.println(gpsEncodedValue);
    displayInfo();
  }


}
void displayInfo() {
  Serial.print(F("Location: ")); 
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print(F("INVALID"));
  }
}