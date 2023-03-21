// Pin definitions
#define A_PIN 2
#define B_PIN 3
#define C_PIN 4
#define D_PIN 5
#define OE_PIN 6
#define STB_PIN 10
#define R1_PIN 11
#define CLK_PIN 13

// Buffer to hold the LED data
byte ledBuffer[128]; // 64 columns * 2 bytes per column

void setup() {
  // Set pin modes
  pinMode(A_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(C_PIN, OUTPUT);
  pinMode(D_PIN, OUTPUT);
  pinMode(OE_PIN, OUTPUT);
  pinMode(STB_PIN, OUTPUT);
  pinMode(R1_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  
  // Initialize pins
  digitalWrite(OE_PIN, LOW); // Enable output
  digitalWrite(STB_PIN, LOW); // Set STB low to start
  
  // Clear the LED buffer
  clearLedBuffer();
}

void loop() {
  // Example: draw a diagonal line
  for (int i = 0; i < 64; i++) {
    setLed(i, i, true);
  }
  
  // Display the LED buffer
  displayLedBuffer();
  
  delay(1000); // Wait for 1 second
}

// Set the state of a single LED
void setLed(int x, int y, boolean state) {
  // Calculate the index in the LED buffer
  int index = (y * 2) + (x / 8);
  
  // Calculate the bit mask
  byte mask = 1 << (7 - (x % 8));
  
  // Update the LED buffer
  if (state) {
    ledBuffer[index] |= mask; // Set the bit
  } else {
    ledBuffer[index] &= ~mask; // Clear the bit
  }
}

// Clear the LED buffer
void clearLedBuffer() {
  for (int i = 0; i < 128; i++) {
    ledBuffer[i] = 0;
  }
}

// Display the LED buffer
void displayLedBuffer() {
  // Write the LED buffer to the display
  for (int col = 0; col < 64; col++) {
    // Set the row data for the current column
    for (int row = 0; row < 16; row++) {
      int index = (row * 2) + (col / 8);
      byte mask = 1 << (7 - (col % 8));
      boolean state = ledBuffer[index] & mask;
      digitalWrite(R1_PIN, state);
      pulseClock();
    }
    
    // Latch the row data for the current column
    digitalWrite(STB_PIN, HIGH);
    pulseClock();
    digitalWrite(STB_PIN, LOW);
  }
}

// Pulse the clock pin
void pulseClock() {
  digitalWrite(CLK_PIN, HIGH);
  digitalWrite(CLK_PIN, LOW);
}

// Set the address pins for the current column
void setAddress(int col) {
  digitalWrite(A_PIN, (col >> 0) & 1);
  digitalWrite(B_PIN, (col >> 1) & 1);
  digitalWrite(C_PIN, (col >> 2) & 1);
  digitalWrite(D_PIN, (col >> 3) & 1);
}
