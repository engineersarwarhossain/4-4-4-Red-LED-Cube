// ——————————————————————————————
// 4×4×4 LED Cube: Z-Axis Plane Sweep Animation
// ——————————————————————————————

const uint8_t layerPins[4] = {2, 3, 4, 5};     // Layers (Z-axis: 0–3)
const uint8_t colPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5,
  0,  1           // D0, D1 used as digital outputs
};

uint16_t cubeData[4];  // Buffer for 4 layers

// ——————————————————————————————
// Helper: Clear the entire cube
// ——————————————————————————————
void clearCube() {
  for (uint8_t z = 0; z < 4; z++)
    cubeData[z] = 0;
}

// ——————————————————————————————
// Helper: Light all 16 LEDs of a layer
// ——————————————————————————————
void fillLayer(uint8_t z) {
  if (z < 4)
    cubeData[z] = 0xFFFF; // 16 bits ON
}

// ——————————————————————————————
// Helper: Draw one full frame
// ——————————————————————————————
void drawCubeFrame() {
  for (uint8_t z = 0; z < 4; z++) {
    for (uint8_t i = 0; i < 16; i++) {
      digitalWrite(colPins[i], (cubeData[z] & (1 << i)) ? HIGH : LOW);
    }
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(1000);  // layer dwell time
    digitalWrite(layerPins[z], LOW);
  }
}

// ——————————————————————————————
// Animation: Plane Sweep Z=0 → 3 → 0
// ——————————————————————————————
void animPlaneSweep(uint8_t repeat = 3, uint16_t holdDelay = 100) {
  for (uint8_t r = 0; r < repeat; r++) {
    // Z = 0 → 3 (up)
    for (uint8_t z = 0; z < 4; z++) {
      clearCube();
      fillLayer(z);
      drawCubeFrame();
      delay(holdDelay);
    }

    // Z = 2 → 1 (down) (skip z=3 to avoid repeat)
    for (int8_t z = 2; z >= 0; z--) {
      clearCube();
      fillLayer(z);
      drawCubeFrame();
      delay(holdDelay);
    }
  }
}

// ——————————————————————————————
// Arduino Setup & Main Loop
// ——————————————————————————————
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
  animPlaneSweep();  // play the sweep
  delay(1000);       // pause before repeat
}
