#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <ezButton.h>

#define PIN 7
#define VRX_PIN A1
#define VRY_PIN A0
#define STEPS 100
#define NUMPIXELS 14     // make this higher to slow down
#define SW 2

//Din connects to pin 11
//CLK connects to pin 13

int pinCS = 10; 
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;
int dela = 10;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

const unsigned char PROGMEM up[] = {
  B00011000,
  B00100100,
  B01000010,
  B01111110,
  B00011000,
  B00011000,
  B00011000,
  B00011000
};

const unsigned char PROGMEM down[] = {
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B01111110,
  B01000010,
  B00100100,
  B00011000
};

const unsigned char PROGMEM left[] = {
  B00000000,
  B00110000,
  B01010000,
  B10011111,
  B10011111,
  B01010000,
  B00110000,
  B00000000
};

const unsigned char PROGMEM right[] = {
  B00000000,
  B00001100,
  B00001010,
  B11111001,
  B11111001,
  B00001010,
  B00001100,
  B00000000
};


const unsigned char PROGMEM nothing[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
ezButton button(SW);


int xValue = 0;
int yValue = 0;
int bValue = 0; 
int color[3] = {0, 0, 0};

void setup() {
  pixels.begin();
  Serial.begin(9600);
  matrix.setIntensity(10);

}
 
 
void loop() {
  button.loop();
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  
bValue = button.getState();

  if (button.isPressed()) {
    Serial.println("The button is pressed");
     matrix.drawBitmap(0, 0, nothing, 8, 8, LOW);
    matrix.write();
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    // TODO do something here
  }
  
  stickman(color[0], color[1], color[2], dela);
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(color[0], color[1], color[2]));
    delay(dela);
    pixels.show();
  }
}

void stickman(int &red, int &green, int &blue, int &dela) {
  if(xValue > 480 && xValue < 520 && yValue > 950 && yValue < 1030){
    red = rand() % 257 + 1;
    green = rand() % 257 + 1;
    blue = rand() % 257 + 1;
    matrix.drawBitmap(0, 0, left, 8, 8, HIGH);
    matrix.write();
  }
  else if(xValue > 950 && xValue < 1030 && yValue > 400 && yValue < 1000){
    red = 0;
    green = 0;
    blue = 0;
    Serial.println("test");
    matrix.drawBitmap(0, 0, down, 8, 8, HIGH);
    matrix.write();

  }
  else if(xValue > 0 && xValue < 950 && yValue > 0 && yValue < 400){
    Serial.println("right");
    matrix.drawBitmap(0, 0, right, 8, 8, HIGH);
    matrix.write();
    dela = 100;
  }
  else if(xValue > 0 && xValue < 150 && yValue > 0 && yValue < 1000){
    Serial.println("up");
    matrix.drawBitmap(0, 0, up, 8, 8, HIGH);
    matrix.write();
    int x = 0;
    for(int i=0; i<NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(color[0], color[1], color[2]));
      delay(100);
      if(x == i-1){
        pixels.setPixelColor(x, pixels.Color(0, 0, 0));  
        x++;          
      }
      pixels.show();
    }
  }
  else {
    matrix.drawBitmap(0, 0, left, 8, 8, LOW);    
    matrix.drawBitmap(0, 0, down, 8, 8, LOW);    
    matrix.drawBitmap(0, 0, right, 8, 8, LOW);
    matrix.drawBitmap(0, 0, up, 8, 8, LOW);
    dela = 10;
  }
}