/*
  LED Cube 4×4×4 — Overlapping Random Fade Animations

  Multiple LEDs will independently light up at random times,
  each fading out smoothly over a fixed duration. New fades
  spawn continuously, but no two fades start at exactly the
  same moment.

  You can adjust:
    • ledOnTimeMs    — total “alive” time per LED (ms)
    • fadeSteps      — how many discrete brightness levels
    • spawnChancePct — percent chance (per frame) to start a new fade
    • maxActiveFades — maximum simultaneous fades
*/

#include <Arduino.h>

// ───── USER-ADJUSTABLE PARAMETERS ─────
const uint16_t ledOnTimeMs    = 2000;  // fade duration per LED
const uint8_t  fadeSteps      = 20;    // discrete brightness levels
const uint8_t  spawnChancePct = 5;     // 5% chance each frame to spawn new fade
const uint8_t  maxActiveFades = 8;     // up to 8 simultaneous fades

// ───── CUBE CONFIGURATION ─────
const uint8_t SIZE_X = 4;
const uint8_t SIZE_Y = 4;
const uint8_t SIZE_Z = 4;
const uint8_t TOTAL_LEDS = SIZE_X * SIZE_Y * SIZE_Z;

// Layers (common anode) and columns (sinks)
const uint8_t layerPins[SIZE_Z] = {2, 3, 4, 5};
const uint8_t colPins[SIZE_X * SIZE_Y] = {
  6, 7, 8, 9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, A6, A7
};

// ───── LOW-LEVEL DRIVERS —─────
// Turn all LEDs off immediately.
void clearCube() {
  for (uint8_t z = 0; z < SIZE_Z; z++) {
    digitalWrite(layerPins[z], LOW);
  }
  for (uint8_t c = 0; c < TOTAL_LEDS / SIZE_Z; c++) {
    digitalWrite(colPins[c], LOW);
  }
}

// Latch/update frame (no-op for direct multiplexing)
void drawCubeFrame() {}

// Set a voxel at given brightness (0–255). >0 lights it.
// Replace with PWM driver code if available.
void setVoxelIntensity(uint8_t x, uint8_t y, uint8_t z, uint8_t intensity) {
  if (intensity == 0) return;
  uint8_t layer = z;
  uint8_t col   = y * SIZE_X + x;
  digitalWrite(layerPins[layer], HIGH);
  digitalWrite(colPins[col], HIGH);
}

// ───── FADE EVENT STRUCTURE ─────
struct Fade {
  uint8_t x, y, z;
  unsigned long startMs;
};
Fade activeFades[maxActiveFades];
uint8_t fadeCount = 0;

// ───── SETUP & LOOP ─────
void setup() {
  // initialize pins
  for (uint8_t i = 0; i < SIZE_Z; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }
  for (uint8_t i = 0; i < TOTAL_LEDS / SIZE_Z; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
  randomSeed(analogRead(A0));
}

void loop() {
  unsigned long now = millis();

  // --- spawn new fade event? ---
  if (fadeCount < maxActiveFades && random(100) < spawnChancePct) {
    // pick a random LED position
    uint8_t flat = random(TOTAL_LEDS);
    Fade f;
    f.x = flat % SIZE_X;
    f.y = (flat / SIZE_X) % SIZE_Y;
    f.z = flat / (SIZE_X * SIZE_Y);
    f.startMs = now;
    activeFades[fadeCount++] = f;
  }

  clearCube();

  // --- update all active fades ---
  for (int8_t i = fadeCount - 1; i >= 0; i--) {
    unsigned long elapsed = now - activeFades[i].startMs;
    if (elapsed >= ledOnTimeMs) {
      // remove this fade (swap-and-pop)
      activeFades[i] = activeFades[--fadeCount];
    } else {
      // compute brightness: 255 → 0 over time
      uint8_t step = map(elapsed, 0, ledOnTimeMs, 0, fadeSteps);
      uint8_t brightness = map(fadeSteps - step, 0, fadeSteps, 0, 255);
      setVoxelIntensity(activeFades[i].x,
                        activeFades[i].y,
                        activeFades[i].z,
                        brightness);
    }
  }

  drawCubeFrame();

  // small frame delay (controls smoothness)
  delay(ledOnTimeMs / fadeSteps / 2);
}
