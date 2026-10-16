// 4×4×4 LED Cube: Combined Plane Sweep & Rain Drop Animations
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

// Animation speed & duration settings
const uint8_t  rainDropsCount = 500;    // Total raindrops per cycle
const uint16_t rainDelayMs      = 80;  // Delay per rain frame in ms

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

// Draw one multiplexed frame
void drawCubeFrame() {
  for (uint8_t z = 0; z < 4; z++) {
    for (uint8_t i = 0; i < 16; i++) {
      digitalWrite(colPins[i], (cubeData[z] & (1 << i)) ? HIGH : LOW);
    }
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(1000);
    digitalWrite(layerPins[z], LOW);
  }
}

// Rain Drop Effect Animation
// drops: number of raindrops to generate
// delayMs: delay per frame
void animRain(uint16_t drops = rainDropsCount, uint16_t delayMs = rainDelayMs) {
  struct Drop { uint8_t col, z; } active[16];
  uint8_t count = 0;

  unsigned long start = millis();
  while (millis() - start < drops * delayMs) {
    // Spawn new drop randomly
    if (count < 16 && random(0, 10) > 6) {
      active[count++] = { uint8_t(random(0,16)), 3 };
    }
    clearCube();
    // Update drops
    for (uint8_t i = 0; i < count; i++) {
      uint8_t x = active[i].col % 4;
      uint8_t y = active[i].col / 4;
      setVoxel(x, y, active[i].z, true);
      if (active[i].z > 0) active[i].z--;
      else { active[i] = active[--count]; i--; }
    }
    drawCubeFrame();
    delay(delayMs);
  }
}

// Plane Sweep Animation for axis 'X','Y','Z'
void animPlaneSweep(char axis, uint8_t repeat = 2, uint16_t delayMs = 150) {
  for (uint8_t r = 0; r < repeat; r++) {
    if (axis == 'X') {
      for (uint8_t x = 0; x < 4; x++) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame(); delay(delayMs);
      }
      for (int8_t x = 2; x >= 0; x--) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame(); delay(delayMs);
      }
    } else if (axis == 'Y') {
      for (uint8_t y = 0; y < 4; y++) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t x = 0; x < 4; x++) setVoxel(x, y, z, true);
        drawCubeFrame(); delay(delayMs);
      }
      for (int8_t y = 2; y >= 0; y--) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t x = 0; x < 4; x++) setVoxel(x, y, z, true);
        drawCubeFrame(); delay(delayMs);
      }
    } else if (axis == 'Z') {
      for (uint8_t z = 0; z < 4; z++) {
        clearCube();
        for (uint8_t x = 0; x < 4; x++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame(); delay(delayMs);
      }
      for (int8_t z = 2; z >= 0; z--) {
        clearCube();
        for (uint8_t x = 0; x < 4; x++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame(); delay(delayMs);
      }
    }
  }
}

void setup() {
  randomSeed(analogRead(0));
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(layerPins[i], OUTPUT); digitalWrite(layerPins[i], LOW);
  }
  for (uint8_t i = 0; i < 16; i++) {
    pinMode(colPins[i], OUTPUT); digitalWrite(colPins[i], LOW);
  }
}

void loop() {
  animPlaneSweep('X', 2, 100);
  delay(200);
  animPlaneSweep('Y', 2, 100);
  delay(200);
  animPlaneSweep('Z', 2, 100);
  delay(500);
  // Use defaults or override raindrop parameters below
  animRain();            // uses rainDropsCount & rainDelayMs
  // animRain(30, 120);   // custom: 30 drops, 120ms delay
  delay(1000);
}
