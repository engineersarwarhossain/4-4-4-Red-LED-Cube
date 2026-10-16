// 4×4×4 LED Cube: Smooth Global Glow Animation
// Arduino Nano

#include <Arduino.h>

// --- Pin definitions ---
// layerPins: common cathode pins controlling each of the 4 layers (z = 0..3)
const uint8_t layerPins[4] = {2, 3, 4, 5};
// colPins: anode pins for 16 columns (x,y) mapped row-major y*4 + x
const uint8_t colPins[16]  = {
  6,  7,  8,  9,    // y = 0, x = 0..3
  10, 11, 12, 13,  // y = 1
  A0, A1, A2, A3,  // y = 2
  A4, A5, 0,  1    // y = 3
};

// --- Glow cycle settings ---
// Glow parameters (edit in code):
// BASE_BRIGHTNESS: minimum brightness factor at pulse trough (0.0 = off, 1.0 = full)
// AMPLITUDE: how much above BASE to pulse (peak = BASE + AMPLITUDE, must ≤ 1.0)
// SPEED_RATE: how much to advance the sine-phase each loop (larger = faster pulsing)
const float BASE_BRIGHTNESS = 0.2f;
const float AMPLITUDE       = 0.8f;
const float SPEED_RATE      = 0.05f;

// PWM_PERIOD: total microseconds per on/off cycle for each layer
// Longer period = lower refresh rate but finer brightness control
const uint32_t PWM_PERIOD = 2000;

// --- Initialize I/O pins ---
void initPins() {
  // Configure each layer pin as OUTPUT and set LOW (off for common cathode)
  for (uint8_t z = 0; z < 4; z++) {
    pinMode(layerPins[z], OUTPUT);
    digitalWrite(layerPins[z], LOW);
  }
  // Configure each column pin as OUTPUT and set LOW (off for anode)
  for (uint8_t c = 0; c < 16; c++) {
    pinMode(colPins[c], OUTPUT);
    digitalWrite(colPins[c], LOW);
  }
}

// --- Draw one multiplexed frame at given brightness ---
// brightness: 0.0 (dark) → 1.0 (bright)
void drawFrame(float brightness) {
  // Calculate ON vs OFF durations within PWM_PERIOD
  uint32_t onTime  = (uint32_t)(PWM_PERIOD * brightness);
  uint32_t offTime = PWM_PERIOD - onTime;

  // Multiplex through each of the 4 layers
  for (uint8_t z = 0; z < 4; z++) {
    // Turn on all column lines (anodes)
    for (uint8_t c = 0; c < 16; c++) {
      digitalWrite(colPins[c], HIGH);
    }
    // Enable this layer (drive cathode LOW)
    digitalWrite(layerPins[z], HIGH);
    // Keep on for onTime microseconds
    delayMicroseconds(onTime);
    // Disable layer
    digitalWrite(layerPins[z], LOW);
    // Wait remaining time to complete PWM_PERIOD
    delayMicroseconds(offTime);
  }
}

void setup() {
  // Prepare all I/O
  initPins();
}

void loop() {
  static float phase = 0.0f;
  // Compute brightness from a sine wave: between BASE and BASE+AMPLITUDE
  float sinVal = sin(phase);
  float b = BASE_BRIGHTNESS + AMPLITUDE * (0.5f + 0.5f * sinVal);
  // Constrain to valid 0.0..1.0
  b = constrain(b, 0.0f, 1.0f);
  // Render one frame at brightness b
  drawFrame(b);
  // Advance phase for next loop
  phase += SPEED_RATE;
}