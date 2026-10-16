// ————————————————————————————————
// 4×4×4 LED Cube: X‑Axis Plane Sweep
// ————————————————————————————————

const uint8_t layerPins[4] = {2, 3, 4, 5};     // Z layers 0–3
const uint8_t colPins[16] = {
  6,  7,  8,  9,        // X=0, Y=0–3
  10, 11, 12, 13,       // X=1, Y=0–3
  A0, A1, A2, A3,       // X=2, Y=0–3
  A4, A5,               // X=3, Y=0–1
  0,  1                 // X=3, Y=2–3 (using D0/D1)
};

uint16_t cubeData[4];    // [z] → 16‑bit mask of (x,y)

// ————————————————————————————————
// Helpers
// ————————————————————————————————
void clearCube() {
  for (uint8_t z = 0; z < 4; z++) cubeData[z] = 0;
}

void setVoxel(uint8_t x, uint8_t y, uint8_t z, bool on) {
  if (x>3||y>3||z>3) return;
  uint8_t bit = y*4 + x;
  if (on)  cubeData[z] |=  (1 << bit);
  else     cubeData[z] &= ~(1 << bit);
}

void drawCubeFrame() {
  for (uint8_t z = 0; z < 4; z++) {
    // set columns for this layer
    for (uint8_t i = 0; i < 16; i++) {
      bool ledOn = (cubeData[z] & (1 << i));
      digitalWrite(colPins[i], ledOn ? HIGH : LOW);
    }
    // enable layer z
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(1000);
    digitalWrite(layerPins[z], LOW);
  }
}

// ————————————————————————————————
// X‑Plane Sweep Animation
// ————————————————————————————————
void animPlaneSweepX(uint8_t repeat = 3, uint16_t holdDelay = 150) {
  for (uint8_t r = 0; r < repeat; r++) {

    // Front to Back: X = 0 → 3
    for (uint8_t x = 0; x < 4; x++) {
      clearCube();
      for (uint8_t z = 0; z < 4; z++) {
        for (uint8_t y = 0; y < 4; y++) {
          setVoxel(x, y, z, true);
        }
      }
      drawCubeFrame();
      delay(holdDelay);
    }

    // Back to Front: X = 2 → 0 (skip X=3 to avoid duplicate frame)
    for (int8_t x = 2; x >= 0; x--) {
      clearCube();
      for (uint8_t z = 0; z < 4; z++) {
        for (uint8_t y = 0; y < 4; y++) {
          setVoxel(x, y, z, true);
        }
      }
      drawCubeFrame();
      delay(holdDelay);
    }
  }
}

// ————————————————————————————————
// Setup & Loop
// ————————————————————————————————
void setup() {
  // layers off
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }
  // columns off
  for (uint8_t i = 0; i < 16; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
}

void loop() {
  animPlaneSweepX();   // run the X‑axis sweep
  delay(1000);         // pause before next cycle
}
