#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Choose two Arduino pins to use for software serial
int RXPin = 2;
int TXPin = 3;

int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(100);
}
