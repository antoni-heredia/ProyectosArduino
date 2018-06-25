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

const int led = 13;
int rojo, verde, azul, modo;
char mensaje[255];
int lon = 0;
void setup() {
  BT1.begin(9600);
  Serial.begin(9600);

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(led, OUTPUT);

  //Inicializao los colores
  rojo = 0;
  azul = 255;
  verde = 0;

}

void loop() {

  if (BT1.available() > 0) {

    //leeemos la opcion
    char  dato = BT1.read();;

    if (dato != '$') {
      mensaje[lon] = dato;
      lon ++;

    } else {

      mensaje[lon] = '\0';
      int i;
      String opcion;

      for ( i = 0; i < lon && mensaje[i] != '#'; i++) {
        opcion += mensaje[i];

      }

      if (opcion == "color") {

        String numRojo;
        i++;
        for (int o = 0; i < lon && mensaje[i] != '#'; i++, o++)
          numRojo += mensaje[i];


        String numVerde;
        i++;
        for (int o = 0; i < lon && mensaje[i] != '#'; i++, o++)
          numVerde += mensaje[i];

        String numAzul;
        i++;
        for (int o = 0; i < lon && mensaje[i] != '#'; i++, o++)
          numAzul += mensaje[i];

        rojo = numRojo.toInt();
        verde = numVerde.toInt();
        azul = numAzul.toInt();
        Serial.print(rojo);
        Serial.print(verde);
        Serial.print(azul);


      } else if (opcion == "modo") {

        //      modo = lectura().toInt();
        modo = (int)mensaje[i + 1];

        switch (mensaje[i + 1]) {

          case '0':
            for (int i = 0; i < NUMPIXELS; i++) {

              // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
              if (corazon[i] == 1)
                strip.setPixelColor(i, strip.Color(rojo, verde, azul)); // Moderately bright green color.
              else
                strip.setPixelColor(i, strip.Color(0, 0, 0)); // Moderately bright green color.

              strip.show(); // This sends the updated pixel color to the hardware.


            }
            break;

          case '1':
            for (int i = 0; i < NUMPIXELS; i++) {

              // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
              if (todoPintado[i] == 1)
                strip.setPixelColor(i, strip.Color(rojo, verde, azul)); // Moderately bright green color.
              else
                strip.setPixelColor(i, strip.Color(0, 0, 0)); // Moderately bright green color.

              strip.show(); // This sends the updated pixel color to the hardware.


            }
            break;
        }
      } else if (opcion == "personalizado") {
        i++;
        for (int o = 0; o < NUMPIXELS; o++, i++) {

          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
          if (mensaje[i] == '1'){
            Serial.print("entra");
            strip.setPixelColor(o, strip.Color(rojo, verde, azul)); // Moderately bright green color.
          }else
            strip.setPixelColor(o, strip.Color(0, 0, 0)); // Moderately bright green color.
        }
        strip.show(); // This sends the updated pixel color to the hardware.

      }
      lon = 0;
      mensaje[lon] = '\0';
    }
   
  }
}




