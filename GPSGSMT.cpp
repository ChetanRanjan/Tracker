# include <SoftwareSerial.h>
# include <TinyGPS++.h>

static const int gpsTX_PIN = 11, gpsRX_PIN = 10;
static const int gsmTX_PIN = 3, gsmRX_PIN = 2;
static const serialBaud = 9600;
static const gpsBaud = 9600;
static const gsmBaud = 115200;
uint8_t gpsSignalIndicator=  12;

String[] myContacts = {"+919513066050", "+919845239908", "+919845638636"};
static const mmn = "+919513066050";

//creating tinygps 
TinyGPSPlus gps;

//serial communication for gps, gsm and serial communication
SoftwareSerial gpsSerial(gpsTX_PIN, gpsRX_PIN);
SoftwareSerial gsmSerial(gsmTX_PIN, gsmRX_PIN);



void setup(){
    gpsSerial.begin(gpsBaud);
    gsmSerial.begin(gsmBaud);
    
}
//  https://www.google.com/maps?q=loc:12.89925733032358,77.6518600514714
String locationData(){
    String locationMessage = "";
    if(gps.location.isValid()){
        locationMessage = "https://www.google.com/maps?q=loc:";
        digitalWrite(gpsSignalIndicator, HIGH);
        locationMessage+=(gps.location.lat(), 14)+",";
        locationMessage+=(gps.location.lng(), 14);
    }
    else{
        digitalWrite(gpsSignalIndicator, HIGH);
        delay(200);
        digitalWrite(gpsSignalIndicator, LOW);
        delay(300);
    }
    if(gps.date.isValid()){
        locationMessage+="\n Date: "+gps.date.day()+"//"+gps.date.month()+"//"+gps.date.year()+"\n";
    }else{
        locationMessage+="\n Date: \n";
    }
    if(gps.time.isValid()){
        if(gps.time.hour() < 10)
            locationMessage+="0";
        locationMessage+=(gps.time.hour())+":";
        if(gps.time.minute() < 10)
            locationMessage+="0";
        locationMessage+=(gps.time.minute())+":";
        if(gps.time.second() < 10)
            locationMessage+="0";
        locationMessage+=(gps.time.second())+":";
    }
    return locationMessage;
}


void sendATPCommand(String cmd, String expectedRes, int timeoutsInMilliSec){
	gsmSerial.println(cmd);
	String response = "";
	long timeStart = millis();
	while((millis()-timeStart)<timeoutsInMilliSec){
		while(gsmSerial.available()>0){
			char c = gsmSerial.read();
			response+ = c;
		}
		if(response.indexOf(expectedRes)! = -1){
			break;
		}
	}
	Serial.println(response);
}




