#include <Adafruit_NeoPixel.h>

#define PIN 6

#define NUMPIXELS 16

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear();

  for (int i=0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(rand() % (255 + 1), 16, 16));
    pixels.show();
    delay(100);
  }
}
