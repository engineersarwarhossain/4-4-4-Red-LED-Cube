// ————————————————————————————————
// 4×4×4 LED Cube: Y-Axis Plane Sweep Animation
// ————————————————————————————————

const uint8_t layerPins[4] = {2, 3, 4, 5};     // Z layers
const uint8_t colPins[16] = {
  6,  7,  8,  9,         // X=0–3, Y=0
  10, 11, 12, 13,       // X=0–3, Y=1
  A0, A1, A2, A3,       // X=0–3, Y=2
  A4, A5,               // X=0–1, Y=3
  0, 1                  // X=2–3, Y=3
};

uint16_t cubeData[4];   // Each layer (Z) = 16 bits (4×4 plane)

// ————————————————————————————————
// Helpers
// ————————————————————————————————

void clearCube() {
  for (uint8_t z = 0; z < 4; z++)
    cubeData[z] = 0;
}

void setVoxel(uint8_t x, uint8_t y, uint8_t z, bool state) {
  if (x > 3 || y > 3 || z > 3) return;
  uint8_t bitIndex = y * 4 + x;
  if (state) cubeData[z] |= (1 << bitIndex);
  else       cubeData[z] &= ~(1 << bitIndex);
}

void drawCubeFrame() {
  for (uint8_t z = 0; z < 4; z++) {
    for (uint8_t c = 0; c < 16; c++) {
      digitalWrite(colPins[c], (cubeData[z] & (1 << c)) ? HIGH : LOW);
    }
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(1000);
    digitalWrite(layerPins[z], LOW);
  }
}

// ————————————————————————————————
// Y-Plane Sweep Animation (Right to Left, then Left to Right)
// ————————————————————————————————
void animPlaneSweepY(uint8_t repeat = 3, uint16_t holdDelay = 150) {
  for (uint8_t r = 0; r < repeat; r++) {
    // Y = 0 → 3 (Right to Left)
    for (uint8_t y = 0; y < 4; y++) {
      clearCube();
      for (uint8_t z = 0; z < 4; z++) {
        for (uint8_t x = 0; x < 4; x++) {
          setVoxel(x, y, z, true);
        }
      }
      drawCubeFrame();
      delay(holdDelay);
    }

    // Y = 2 → 0 (Left to Right, skipping Y=3 again)
    for (int8_t y = 2; y >= 0; y--) {
      clearCube();
      for (uint8_t z = 0; z < 4; z++) {
        for (uint8_t x = 0; x < 4; x++) {
          setVoxel(x, y, z, true);
        }
      }
      drawCubeFrame();
      delay(holdDelay);
    }
  }
}

// ————————————————————————————————
// Setup and Loop
// ————————————————————————————————
void setup() {
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }
  for (uint8_t i = 0; i < 16; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
}

void loop() {
  animPlaneSweepY();
  delay(1000);
}
