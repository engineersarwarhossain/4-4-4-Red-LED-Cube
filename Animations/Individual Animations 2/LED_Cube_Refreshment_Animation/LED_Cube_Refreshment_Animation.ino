// 4×4×4 LED Cube – 🔄 Refreshment Animation (Common‑Cathode w/ NPN Low‑Side)

// == Pin Definitions ==
const int columnPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, 0,  1
};
const int layerPins[4] = { 2, 3, 4, 5 };  // NPN transistor bases

void setup() {
  // Columns OFF (anodes LOW)
  for (int c = 0; c < 16; c++) {
    pinMode(columnPins[c], OUTPUT);
    digitalWrite(columnPins[c], LOW);
  }
  // Layers OFF (transistors off = LOW)
  for (int l = 0; l < 4; l++) {
    pinMode(layerPins[l], OUTPUT);
    digitalWrite(layerPins[l], LOW);
  }
}

void loop() {
  refreshmentAnimation();
  delay(500);  // pause before repeating
}


// 🔄 Refreshment Animation (Common‑Cathode w/ NPN Low‑Side)
//   – LEDs fill from layer 0→3, hold 4 s, then empty from 3→0

void refreshmentAnimation() {
  const int FILL_STEP_DELAY  = 500;   // ms between lighting each layer
  const int HOLD_TIME        = 3000;  // ms to hold all LEDs on
  const int EMPTY_STEP_DELAY = 500;   // ms between turning each layer off

  // 1) Clear everything
  for (int c = 0; c < 16; c++) digitalWrite(columnPins[c], LOW);
  for (int l = 0; l < 4;  l++) digitalWrite(layerPins[l],  LOW);

  // 2) Fill from bottom (layer 0) to top (layer 3)
  for (int l = 0; l < 4; l++) {
    digitalWrite(layerPins[l], HIGH);        // turn layer l on
    for (int c = 0; c < 16; c++)             // turn all columns on
      digitalWrite(columnPins[c], HIGH);
    delay(FILL_STEP_DELAY);
  }

  // 3) Hold all LEDs lit
  delay(HOLD_TIME);

  // 4) Empty from top (layer 3) down to bottom (layer 0)
  for (int l = 3; l >= 0; l--) {
    digitalWrite(layerPins[l], LOW);         // turn layer l off
    delay(EMPTY_STEP_DELAY);
  }

  // 5) Finally clear all columns as well
  for (int c = 0; c < 16; c++) digitalWrite(columnPins[c], LOW);
}
