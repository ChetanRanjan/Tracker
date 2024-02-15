 #include <SoftwareSerial.h>
SoftwareSerial sim800l(2, 3);            // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted

static int button1 = 4;                      //Button pin, on the other pin it's wired with GND
  bool button_State; //Button state
  void setup()
   {

   pinMode(button1, INPUT_PULLUP);  //The button is always on HIGH level, when pressed it  goes LOW
     sim800l.begin(115200);        //Module baude rate, this is on max, it depends on the version
      Serial.begin(115200);
      delay(1000);
      Serial.println("Button pressed");   //Shows this message on the serial monitor
     }

  void loop()
  {

  button_State = digitalRead(button1);   //We are constantly reading the button State
  if (button_State == LOW) {            //And if it's pressed
  Serial.println("Button pressed");   //Shows this message on the serial monitor
  delay(200);                      //Small delay to avoid detecting the button press many times
  SendSMS();                          //And this function is called

  }

if (sim800l.available()){   //Displays on the serial monitor if there's a communication from the module
Serial.write(sim800l.read());
}
}

void SendSMS(){
if(sim800l.available() > 0){
  Serial.println("OK");
}
else{
  Serial.println("ERROR");
}
Serial.println("Sending SMS...");               //Show this message on serial monitor
sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
delay(100);
sim800l.print("AT+CMGS=\"+919513066050\"\r");      //Your phone number don't forget to include your country code, example +212123456789"
delay(500);
sim800l.print("I AM ALIVE!!");   //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
delay(500);
sim800l.print((char)26);                 // (required according to the datasheet)
delay(500);
sim800l.println();
Serial.println("Text Sent.");
delay(500);
}