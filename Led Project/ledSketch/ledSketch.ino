#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NUMPIXELS 14     // make this higher to slow down
#define VRX_PIN A0
#define VRY_PIN A1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int xValue = 0;
int yValue = 0;
int color[3] = {250, 50, 120};

void setup() {
  pixels.begin();
  Serial.begin(9600);
}
 
 
void loop() {
    
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  
  Serial.println(color[0]);
  Serial.println(color[1]);
  Serial.println(color[2]);
  stickman(color[0], color[1], color[2]);



  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(color[0], color[1], color[2]));
    pixels.show();
  }

  delay(100);
}

void stickman(int &red, int &green, int &blue) {
  if(xValue > 500 && xValue < 520 && yValue > 1015 && yValue < 1030){
    red = rand() % 257 + 1;
    green = rand() % 257 + 1;
    blue = rand() % 257 + 1;
  }
}