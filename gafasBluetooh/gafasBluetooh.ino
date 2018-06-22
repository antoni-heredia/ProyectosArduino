#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif



#define PIN            6
#define NUMPIXELS      88
#define BRIGHTNESS 50

SoftwareSerial BT1(10, 11); // RX | TX
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
byte corazon[] = {
  0,  0,  1,  1,  0,  1,  1,  0,  0,  0, 0,  0,  1,  1,  0,  1,  1,  0,  0,  0,
  0,  0,  1,  1,  1,  1,  1,  0,  0,  0, 0,  0,  1,  1,  1,  1,  1,  0,  0,  0,
  0,  0,  1,  1,  1,  1,  1,  0,  0,  0, 0,  0,  1,  1,  1,  1,  1,  0,  0,  0,
  0,  0,  1,  1,  1,  0,  0,  0,         0,  0,  1,  1,  1,  0,  0,  0,
  0,  0,  1,  0,  0,  0,                 0,  0,  1,  0,  0,  0
};

byte todoPintado[] = {
  1, 1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,
  1, 1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,
  1, 1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,
  1,  1, 1,  1,  1,  1,  1,  1,        1,  1, 1,  1,  1,  1,  1,  1,
  1, 1,  1,  1,  1,  1,                1, 1,  1,  1,  1,  1,
};

int option;
const int led = 13;

void setup() {
  BT1.begin(9600);
  
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(led, OUTPUT); 

}

void loop() {

  if (BT1.available() > 0) {

    //leeemos la opcion
    char option = BT1.read();

    //si la opcion esta entre '1' y '9'
    if(option == '0'){
      for (int i = 0; i < NUMPIXELS; i++) {

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        if (todoPintado[i] == 1)
          strip.setPixelColor(i, strip.Color(250, 0, 0)); // Moderately bright green color.

        strip.show(); // This sends the updated pixel color to the hardware.


      }
    }else if (option == '1')
    {
      for (int i = 0; i < NUMPIXELS; i++) {

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        if (corazon[i] == 1)
          strip.setPixelColor(i, strip.Color(250, 0, 0)); // Moderately bright green color.
        else
          strip.setPixelColor(i, strip.Color(0, 0, 0)); // Moderately bright green color.

        strip.show(); // This sends the updated pixel color to the hardware.


      }
    }
    else if (option == '2')
    {
      for (int i = 0; i < NUMPIXELS; i++) {

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        if (corazon[i] == 1)
          strip.setPixelColor(i, strip.Color(0, 250, 0)); // Moderately bright green color.
        else
          strip.setPixelColor(i, strip.Color(0, 0, 0)); // Moderately bright green color.

        strip.show(); // This sends the updated pixel color to the hardware.


      }
    }else if (option == '3')
    {
      for (int i = 0; i < NUMPIXELS; i++) {

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        if (corazon[i] == 1)
          strip.setPixelColor(i, strip.Color(0, 0, 250)); // Moderately bright green color.
        else
          strip.setPixelColor(i, strip.Color(0, 0, 0)); // Moderately bright green color.

        strip.show(); // This sends the updated pixel color to the hardware.


      }
    }
  }
}



