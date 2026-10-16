// 4×4×4 LED Cube: Rain Drop Effect Animation Only
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

// Rain Drop animation settings
const uint16_t rainDropsCount = 50;   // Total raindrops per cycle
const uint16_t rainDelayMs      = 80; // Delay per frame in milliseconds

// Helper: clear all voxels
void clearCube() {
  for (uint8_t z = 0; z < 4; z++) {
    cubeData[z] = 0;
  }
}

// Helper: set one voxel on or off
void setVoxel(uint8_t x, uint8_t y, uint8_t z, bool on) {
  if (x > 3 || y > 3 || z > 3) return;
  uint8_t bit = y * 4 + x;
  if (on) cubeData[z] |=  (1 << bit);
  else    cubeData[z] &= ~(1 << bit);
}

// Draw one multiplexed frame using cubeData
void drawCubeFrame() {
  for (uint8_t z = 0; z < 4; z++) {
    // Set all 16 column pins for this layer
    for (uint8_t i = 0; i < 16; i++) {
      bool ledOn = (cubeData[z] & (1 << i));
      digitalWrite(colPins[i], ledOn ? HIGH : LOW);
    }
    // Activate this layer
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(1000); // 1 ms dwell time
    digitalWrite(layerPins[z], LOW);
  }
}

// Rain Drop Effect Animation
// drops: number of raindrops to generate
// delayMs: delay per frame in ms
void animRain(uint16_t drops = rainDropsCount, uint16_t delayMs = rainDelayMs) {
  struct Drop { uint8_t col, z; } active[16];
  uint8_t count = 0;

  unsigned long startTime = millis();
  // Run until total duration elapsed
  while (millis() - startTime < drops * delayMs) {
    // Spawn new drop randomly if below max
    if (count < 16 && random(0, 10) > 6) {
      active[count++] = { uint8_t(random(0, 16)), 3 };
    }
    clearCube();
    // Update and draw each active drop
    for (uint8_t i = 0; i < count; i++) {
      uint8_t x = active[i].col % 4;
      uint8_t y = active[i].col / 4;
      setVoxel(x, y, active[i].z, true);
      if (active[i].z > 0) {
        active[i].z--;
      } else {
        // Remove drop when it reaches bottom
        active[i] = active[--count];
        i--; // adjust index
      }
    }
    drawCubeFrame();
    delay(delayMs);
  }
}

void setup() {
  randomSeed(analogRead(0));
  // Initialize all layer pins
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }
  // Initialize all column pins
  for (uint8_t i = 0; i < 16; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
}

void loop() {
  // Run the rain drop animation
    // Use defaults or override raindrop parameters below
  animRain();            // uses rainDropsCount & rainDelayMs
  // animRain(30, 120);   // custom: 30 drops, 120ms delay
  // Pause before repeating
  delay(1000);
}
