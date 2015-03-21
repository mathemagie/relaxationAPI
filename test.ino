String readstring;
#include <Servo.h> 
#include <SPI.h>
#include <PusherClient.h>
#include <Bridge.h>

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


int led = 13;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int val_eeg;


PusherClient client;
String val;

void setup() {
  
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
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
   val = data.substring(30 + 33);
  Serial.println(val);
  val_eeg = (val.toInt() * 16) / 100;
  Serial.println(val_eeg);
   strip.setPixelColor(val_eeg, strip.Color(127,   0,   0));
   strip.show();
   delay(500);
   strip.setPixelColor(val_eeg, strip.Color(0,   0,   0));
   strip.show();
     
}
