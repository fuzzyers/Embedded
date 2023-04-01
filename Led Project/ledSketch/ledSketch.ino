#include <Adafruit_NeoPixel.h>
#include <Stepper.h>


#define PIN 7
#define NUMPIXELS 14     // make this higher to slow down
#define VRX_PIN A0
#define VRY_PIN A1
#define STEPS 100

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Stepper stepper(STEPS, 8, 9, 10, 11);

int previous = 0;
int xValue = 0;
int yValue = 0;
int color[3] = {0, 0, 0};

void setup() {
  pixels.begin();
  Serial.begin(9600);
  stepper.setSpeed(30);
}
 
 
void loop() {
    
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  
  Serial.print("x ");
  Serial.println(xValue);

  Serial.print("y ");
  Serial.println(yValue);

  stickman(color[0], color[1], color[2]);

  stepper.step(600);

  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(color[0], color[1], color[2]));
    pixels.show();
  }

  delay(100);
}

void stickman(int &red, int &green, int &blue) {
  if(xValue > 480 && xValue < 520 && yValue > 950 && yValue < 1030){
    red = rand() % 257 + 1;
    green = rand() % 257 + 1;
    blue = rand() % 257 + 1;
  }
  else if(xValue > 950 && xValue < 1030 && yValue > 400 && yValue < 480){
    red = 0;
    green = 0;
    blue = 0;
    Serial.println("test");

  }
}