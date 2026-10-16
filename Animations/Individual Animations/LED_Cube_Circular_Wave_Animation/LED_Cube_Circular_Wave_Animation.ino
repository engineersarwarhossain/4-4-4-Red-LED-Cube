// 4×4×4 LED Cube –  🌊 Circular Wave Animation (Common‑Cathode, NPN Transistors)

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
// Layers OFF (NPN off = LOW)
for (int l = 0; l < 4; l++) {
  pinMode(layerPins[l], OUTPUT);
  digitalWrite(layerPins[l], LOW);
}
}

void loop() {
  circularWave();
  delay(10);
}
// 🌊 Circular Wave Animation (Common‑Cathode, NPN Transistors)
//     – LEDs light from center outward in concentric square patterns

void circularWave() {
  const int STEP_DELAY = 500;  // time between wave layers (ms)

  // Concentric square LED groups (per 4×4 layer):
  // Center → Mid → Outer ring
  int waveOrder[4][4] = {
    {5, 6, 9, 10},     // Center square
    {1, 7, 14, 8},      // Next out
    {2, 11, 13, 4},   // Next ring
    {0, 3, 12, 15}     // Corners
  };

  // Loop through each ring (center to outer)
  for (int ring = 0; ring < 4; ring++) {
    for (int layer = 0; layer < 4; layer++) {
      digitalWrite(layerPins[layer], HIGH);   // turn on the layer
      for (int i = 0; i < 4; i++) {
        int col = waveOrder[ring][i];
        digitalWrite(columnPins[col], HIGH);  // light all 4 ring LEDs
      }
      delay(STEP_DELAY);
      for (int i = 0; i < 4; i++) {
        digitalWrite(columnPins[waveOrder[ring][i]], LOW);  // off
      }
      digitalWrite(layerPins[layer], LOW);    // layer off
    }
  }
}
