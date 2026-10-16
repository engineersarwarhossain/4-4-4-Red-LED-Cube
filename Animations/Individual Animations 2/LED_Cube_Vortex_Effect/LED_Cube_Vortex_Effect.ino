// 4×4×4 LED Cube – Layer Stack Vortex Pattern (Common‑Cathode w/ NPN Low‑Side)
// 🔄 Vortex Effect
// == Pin Definitions ==
const int columnPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, 0,  1
};
const int layerPins[4] = { 2, 3, 4, 5 };  // NPN transistor bases via resistors

// == Timing ==
const int ON_TIME       = 30;   // ms each LED is lit
const int GAP_BETWEEN   = 100;  // ms between each stackSize step
const int GAP_SEQUENCE  = 500;  // ms between full up‑and‑down cycle

void setup() {
  // Columns OFF (anodes LOW)
  for (int c = 0; c < 16; c++) {
    pinMode(columnPins[c], OUTPUT);
    digitalWrite(columnPins[c], LOW);
  }
  // Layers OFF (transistors off, cathodes floating HIGH)
  for (int l = 0; l < 4; l++) {
    pinMode(layerPins[l], OUTPUT);
    digitalWrite(layerPins[l], LOW);
  }
}

void loop() {
  // Sequence: 1→2→3→4→3→2→1→0 layers on
  const int stackSeq[] = { 1, 2, 3, 4, 3, 2, 1, 0 };
  const int steps = sizeof(stackSeq) / sizeof(stackSeq[0]);

  // Spiral ordering for the 4×4 plane
 

  // Run through each stack size
  for (int s = 0; s < steps; s++) {
    int stackSize = stackSeq[s];

    // 1) Clear all
    for (int c = 0; c < 16; c++) digitalWrite(columnPins[c], LOW);
    for (int l = 0; l < 4;  l++) digitalWrite(layerPins[l],  LOW);

    // 2) Turn on the bottom 'stackSize' layers
    for (int l = 0; l < stackSize; l++) {
      digitalWrite(layerPins[l], HIGH);
    }

    // 3) For each point in the spiral, light that column
    for (int i = 0; i < 16; i++) {
      digitalWrite(columnPins[i], HIGH);
      delay(ON_TIME);
      digitalWrite(columnPins[i], LOW);
    }

    // 4) Pause before next stackSize
    delay(GAP_BETWEEN);
  }

  // Full cycle done: brief pause then repeat
  delay(GAP_SEQUENCE);
}
