// 4×4×4 LED Cube – Wave Animation Only (Common‑Cathode w/ NPN Low‑Side)

// == Pin Definitions ==
const int columnPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, 0,  1
};
const int layerPins[4] = { 2, 3, 4, 5 };  // NPN transistor bases

// == Timing ==
const int STEP_DELAY = 50;   // ms each LED stays lit
const int LAYER_DELAY = 100; // ms between layers
const int CYCLE_DELAY = 500; // ms between full cycles

void setup() {
  // All columns OFF (anodes LOW)
  for (int c = 0; c < 16; c++) {
    pinMode(columnPins[c], OUTPUT);
    digitalWrite(columnPins[c], LOW);
  }
  // All layers OFF (transistors off = LOW)
  for (int l = 0; l < 4; l++) {
    pinMode(layerPins[l], OUTPUT);
    digitalWrite(layerPins[l], LOW);
  }
}

void loop() {
  waveAnimation();
  delay(CYCLE_DELAY);
}

// 🌊 Wave Animation (Common‑Cathode w/ NPN Low‑Side)
// Lights each column in turn on each layer, creating a “wave” up the cube.
void waveAnimation() {
  for (int l = 0; l < 4; l++) {
    // 1) Clear all columns and layers
    for (int c = 0; c < 16; c++)      digitalWrite(columnPins[c], LOW);
    for (int ll = 0; ll < 4; ll++)    digitalWrite(layerPins[ll], LOW);

    // 2) Activate only layer l
    digitalWrite(layerPins[l], HIGH);

    // 3) Sweep through all 16 columns
    for (int c = 0; c < 16; c++) {
      digitalWrite(columnPins[c], HIGH);
      delay(STEP_DELAY);
      digitalWrite(columnPins[c], LOW);
    }

    // 4) Turn this layer off
    digitalWrite(layerPins[l], LOW);

    // 5) Small gap before next layer
    delay(LAYER_DELAY);
  }
}
