#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NUMPIXELS 14     // make this higher to slow down
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  pixels.begin();
}
 
 
void loop() {
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(rand() % 256 + 1, rand() % 256 + 1, rand() % 256 + 1));
    pixels.show();
    delay(100);
  }
}