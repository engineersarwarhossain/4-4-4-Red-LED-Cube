// 4×4×4 LED Cube: 3D Heartbeat Pulse Animation
// Arduino Nano

#include <Arduino.h>

// --- Pin Definitions ---
// layerPins: common cathodes for layers z=0..3
const uint8_t layerPins[4] = {2, 3, 4, 5};
// colPins: anodes for columns (x,y) row-major y*4 + x
const uint8_t colPins[16] = {
  6,  7,  8,  9,   // y=0, x=0..3
  10, 11, 12, 13,  // y=1
  A0, A1, A2, A3,  // y=2
  A4, A5, 0,  1    // y=3
};

// --- Heartbeat Settings ---
const float BASE_BRIGHTNESS = 0.2f;   // minimum brightness (0.0..1.0)
const float AMPLITUDE       = 0.8f;   // brightness swing range
const float SPEED_RATE      = 0.07f;  // phase increment per loop
const uint32_t PWM_PERIOD   = 1500;   // microseconds per layer cycle

// Initialize pins: columns LOW=off, layers LOW=off for common cathode inversion
void initPins() {
  // Columns: anodes off = LOW
  for (uint8_t c = 0; c < 16; c++) {
    pinMode(colPins[c], OUTPUT);
    digitalWrite(colPins[c], LOW);
  }
  // Layers: cathodes off = LOW
  for (uint8_t z = 0; z < 4; z++) {
    pinMode(layerPins[z], OUTPUT);
    digitalWrite(layerPins[z], LOW);
  }
}

// Compute brightness for heartbeat: two quick peaks per cycle
float heartbeatBrightness(float t) {
  // Create dual peak: sin(t) * sin(t*0.5) yields two pulses
  float beat = sin(t) * sin(t * 0.5f);
  // Normalize to range 0..1
  beat = (beat + 1.0f) * 0.5f;
  // Scale to BASE..BASE+AMPLITUDE
  return BASE_BRIGHTNESS + beat * AMPLITUDE;
}

// Draw one full multiplexed refresh at given brightness
void drawPulseFrame(float brightness) {
  uint32_t onTime  = (uint32_t)(PWM_PERIOD * brightness);
  uint32_t offTime = PWM_PERIOD - onTime;
  for (uint8_t z = 0; z < 4; z++) {
    // Turn on all columns
    for (uint8_t c = 0; c < 16; c++) digitalWrite(colPins[c], HIGH);
    // Activate layer (LOW to sink current)
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(onTime);
    // Deactivate layer
    digitalWrite(layerPins[z], LOW);
    delayMicroseconds(offTime);
  }
}

void setup() {
  initPins();
}

void loop() {
  static float phase = 0.0f;
  // Calculate dynamic brightness
  float b = heartbeatBrightness(phase);
  b = constrain(b, 0.0f, 1.0f);
  // Refresh cube at brightness b
  drawPulseFrame(b);
  // Advance phase for next frame
  phase += SPEED_RATE;
}
