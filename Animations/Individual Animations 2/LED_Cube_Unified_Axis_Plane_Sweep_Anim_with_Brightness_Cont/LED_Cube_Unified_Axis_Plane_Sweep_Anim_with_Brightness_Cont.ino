// 4×4×4 LED Cube: Unified Axis Plane Sweep Animation with Brightness Control
// Speed controlled by constants in code
// Arduino Nano

const uint8_t layerPins[4] = {2, 3, 4, 5};
const uint8_t colPins[16] = {
  6,  7,  8,  9,    // X=0, Y=0–3
  10, 11, 12, 13,   // X=1, Y=0–3
  A0, A1, A2, A3,   // X=2, Y=0–3
  A4, A5,           // X=3, Y=0–1
  0,  1             // X=3, Y=2–3 (D0/D1)
};

uint16_t cubeData[4]; // per-layer 16-bit masks

// Animation speed settings (ms pause per plane)
  //To Change Animation Speed Change the Constant Values
const uint16_t speedDelayX = 100;
const uint16_t speedDelayY = 150;
const uint16_t speedDelayZ = 200;

// Brightness control (0.0 = off, 1.0 = full brightness)
const float BRIGHTNESS = 1.0f;     // Set global brightness here
const uint16_t PWM_PERIOD = 1000;  // microseconds total per layer

// Helper: clear all voxels
void clearCube() {
  for (uint8_t z = 0; z < 4; z++) cubeData[z] = 0;
}

// Helper: set one voxel
void setVoxel(uint8_t x, uint8_t y, uint8_t z, bool on) {
  if (x > 3 || y > 3 || z > 3) return;
  uint8_t bit = y * 4 + x;
  if (on) cubeData[z] |=  (1 << bit);
  else    cubeData[z] &= ~(1 << bit);
}

// Helper: multiplex and draw one frame with brightness
void drawCubeFrame(uint16_t dwellUs = PWM_PERIOD) {
  uint32_t onTime  = (uint32_t)(dwellUs * BRIGHTNESS);
  uint32_t offTime = dwellUs - onTime;

  for (uint8_t z = 0; z < 4; z++) {
    for (uint8_t i = 0; i < 16; i++) {
      digitalWrite(colPins[i], (cubeData[z] & (1 << i)) ? HIGH : LOW);
    }
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(onTime);
    digitalWrite(layerPins[z], LOW);
    delayMicroseconds(offTime);
  }
}

// Unified plane sweep along any axis
// axis: 'X', 'Y', or 'Z'
// repeat: number of full cycles
// delayMs: pause per plane (controls animation speed)
void animPlaneSweepAll(char axis, uint8_t repeat, uint16_t delayMs) {
  for (uint8_t r = 0; r < repeat; r++) {
    if (axis == 'X') {
      for (uint8_t x = 0; x < 4; x++) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
      for (int8_t x = 2; x >= 0; x--) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
    } else if (axis == 'Y') {
      for (uint8_t y = 0; y < 4; y++) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t x = 0; x < 4; x++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
      for (int8_t y = 2; y >= 0; y--) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t x = 0; x < 4; x++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
    } else if (axis == 'Z') {
      for (uint8_t z = 0; z < 4; z++) {
        clearCube();
        for (uint8_t x = 0; x < 4; x++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
      for (int8_t z = 2; z >= 0; z--) {
        clearCube();
        for (uint8_t x = 0; x < 4; x++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
    }
  }
}

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
  // Change animation Repetation by adjusting these constants above
  animPlaneSweepAll('X', 2, speedDelayX);
  delay(200);
  animPlaneSweepAll('Y', 2, speedDelayY);
  delay(200);
  animPlaneSweepAll('Z', 2, speedDelayZ);
  delay(1000);
}
