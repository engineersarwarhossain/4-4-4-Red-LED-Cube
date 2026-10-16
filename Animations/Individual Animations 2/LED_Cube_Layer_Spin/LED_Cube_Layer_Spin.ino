// 4×4×4 LED Cube – Layer Spin Only (Common‑Cathode w/ NPN Low‑Side)

// == Pin Definitions ==
const int columnPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, 0,  1
};
const int layerPins[4] = { 2, 3, 4, 5 };  // NPN transistor bases via resistors

// == Timing ==
const int ON_TIME   = 100;  // ms each sub‑step holds
const int STEP_GAP  = 100;  // ms between each layer step
const int CYCLE_GAP = 500;  // ms between full spin cycles

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
  layerSpin();
  delay(CYCLE_GAP);
}

// 🔃 Layer Spin (Common‑Cathode w/ NPN Low‑Side)
// Shifts a “band” of LEDs around the edges of each layer.
void layerSpin() {
  // Sequence of 4 positions per layer
  // Each sub‑step lights the four corners of that side
  const int seq[4][4] = {
    {0, 1, 2, 3},    // top row
    {3, 7, 11, 15},  // right column
    {12,13,14,15},   // bottom row
    {0, 4, 8, 12}    // left column
  };

  // For each of the 4 sub‑steps…
  for (int step = 0; step < 4; step++) {
    // For each layer 0→3
    for (int l = 0; l < 4; l++) {
      // 1) Clear columns & layers
      for (int c = 0; c < 16; c++)      digitalWrite(columnPins[c], LOW);
      for (int ll = 0; ll < 4; ll++)    digitalWrite(layerPins[ll], LOW);

      // 2) Activate layer l
      digitalWrite(layerPins[l], HIGH);

      // 3) Light the four columns in this sub‑step
      for (int i = 0; i < 4; i++) {
        digitalWrite(columnPins[ seq[step][i] ], HIGH);
      }

      // 4) Hold
      delay(ON_TIME);

      // 5) Turn everything off
      for (int c = 0; c < 16; c++)      digitalWrite(columnPins[c], LOW);
      digitalWrite(layerPins[l], LOW);

      // 6) Small gap before next layer
      delay(STEP_GAP);
    }
  }
}
