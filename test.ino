String readstring;
#include <Servo.h> 
#include <SPI.h>
#include <PusherClient.h>
#include <Bridge.h>


int led = 13;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int val2;


PusherClient client;

String val;

void setup() {
  Serial.begin(9600);
   pinMode(led, OUTPUT);
  Bridge.begin();
  delay(1000);
  Serial.println("coglab pusher setup"); // so I can keep track of what is loaded
   if(client.connect("b8aa4e777b69f94c7803")) {
     client.bind("my_event", set_led);
     client.subscribe("test_channel");
     Serial.println("bind process pusher OK ");
  }
  else {
     Serial.println("BUGGG"); // so I can keep track of what is loaded
  }
}


void loop() {
   // set the brightness of pin 9:
  //analogWrite(led, brightness);    

  // change the brightness for next time through the loop:
  //brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  //if (brightness == 0 || brightness == 255) {
    //fadeAmount = -fadeAmount ; 
  //}     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                
   if (client.connected()) {
        client.monitor();
   }
}

void set_led(String data) {
  Serial.println(data);
   val = data.substring(data.indexOf('data') + 10,data.indexOf('zz'));
  Serial.println(val);
  val2 = val.toInt();
  Serial.println(val2);
  digitalWrite(led, HIGH);   // sets the LED on
  delay(2000);                  // waits for a second
  digitalWrite(led, LOW);    // sets the LED off
  delay(1000);                  // waits for a sec
}
