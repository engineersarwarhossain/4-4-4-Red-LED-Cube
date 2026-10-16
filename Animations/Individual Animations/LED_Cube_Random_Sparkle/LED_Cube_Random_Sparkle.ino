// ————————————————
// 4×4×4 LED Cube: Random Sparkle
// ————————————————

const uint8_t layerPins[4] = {2, 3, 4, 5};
const uint8_t colPins[16]  = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5,
  0,  1   // RX and TX as output for columns
};

uint16_t cubeData[4];  // 4 layers × 16 bits (each bit = 1 LED)

// ————————————————————————
// Helper: set voxel ON or OFF
// ————————————————————————
void setVoxel(uint8_t x, uint8_t y, uint8_t z, bool state) {
  if (x > 3 || y > 3 || z > 3) return;
  uint8_t bitIndex = y * 4 + x;
  if (state) cubeData[z] |=  (1 << bitIndex);
  else       cubeData[z] &= ~(1 << bitIndex);
}

// ————————————————————————
// Helper: clear entire cube
// ————————————————————————
void clearCube() {
  for (uint8_t z = 0; z < 4; z++) cubeData[z] = 0;
}

// ————————————————————————
// Helper: draw one frame
// ————————————————————————
void drawCubeFrame() {
  for (uint8_t z = 0; z < 4; z++) {
    // Set column outputs
    for (uint8_t i = 0; i < 16; i++) {
      digitalWrite(colPins[i], (cubeData[z] & (1 << i)) ? HIGH : LOW);
    }
    // Enable one layer
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(1000);  // 1 ms dwell per layer
    digitalWrite(layerPins[z], LOW);
  }
}

// ————————————————————————
// Random Sparkle Animation
// ————————————————————————
void animSparkle(uint16_t steps = 300, uint8_t sparkleCount = 6, uint16_t delayMs = 50) {
  for (uint16_t i = 0; i < steps; i++) {
    clearCube();
    for (uint8_t s = 0; s < sparkleCount; s++) {
      uint8_t x = random(0, 4);
      uint8_t y = random(0, 4);
      uint8_t z = random(0, 4);
      setVoxel(x, y, z, true);
    }
    drawCubeFrame();
    delay(delayMs);
  }
}

// ————————————————————————
// Arduino Setup & Loop
// ————————————————————————
void setup() {
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }
  for (uint8_t i = 0; i < 16; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }

  randomSeed(analogRead(0)); // Optional: for better randomness
}

void loop() {
  animSparkle();
  delay(500); // pause between sparkle sessions
}
