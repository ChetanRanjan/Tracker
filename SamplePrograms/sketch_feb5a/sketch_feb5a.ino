#include <SoftwareSerial.h>


#define rxPin D3
#define txPin D2
SoftwareSerial mySerial(2,3);


//// UDP
//WiFiUDP UDP;
//IPAddress local_IP(192,168,4,1);
//IPAddress gateway(192,168,4,1);
//IPAddress subnet(255,255,255,0);
//#define UDP_PORT 4210
//
//// UDP Buffer
//char packet[255];
//char reply[] = "Packet received!";

void setup()
{
  Serial.begin(9600);
  

  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  Serial.println("AT");
  mySerial.println("AT");
  updateSerial();
  Serial.println("AT+CSQ");
  mySerial.println("AT+CSQ");
  updateSerial();
  Serial.println("AT+CSCS");
  mySerial.println("AT+CSCS?"); 
  updateSerial();
  Serial.println("AT+CREG");
  mySerial.println("AT+CREG?"); 
  updateSerial();
  Serial.println("AT+CMGF=1");
  mySerial.println("AT+CMGF=1"); 
  updateSerial();
  Serial.println("AT+CMGF=1");
  mySerial.println("AT+CMGF?"); 
  updateSerial();
  Serial.println("AT+CMGS=\"+919513066050\"");
  mySerial.println("AT+CMGS=\"+919513066050\"");
  updateSerial();
  mySerial.print("Last Minute Engineers | lastminuteengineers.com");
  updateSerial();
  mySerial.write(26);
}

void loop()
{
//   // If packet received...
//  int packetSize = UDP.parsePacket();
//  if (packetSize) {
////  Serial.print("Received packet! Size: "); Serial.println(packetSize);
//    int len = UDP.read(packet, 255);
//    if (len > 0) {
//      packet[len] = '\0';
//    }
////  Serial.print("Packet received: ");
//    Serial.println(packet);
// 
//    // Send return packet
//    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
//    UDP.write(reply);
//    UDP.endPacket();
//  }

  
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
}