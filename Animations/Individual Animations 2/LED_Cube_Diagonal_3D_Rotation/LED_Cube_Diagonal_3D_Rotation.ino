// 4×4×4 LED Cube – Diagonal 3D Rotation Only (Common‑Cathode w/ NPN Low‑Side)

// == Pin Definitions ==
const int columnPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, 0,  1
};
const int layerPins[4] = { 2, 3, 4, 5 };  // NPN transistor bases via resistors

// == Timing ==
const int ON_TIME   = 100;  // ms LED on per step
const int STEP_GAP  = 50;   // ms gap between steps
const int CYCLE_GAP = 500;  // ms pause after full rotation

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
  diagonal3DRotation();
  delay(CYCLE_GAP);
}

// 🔺 3D Diagonal Rotation (Common‑Cathode w/ NPN Low‑Side)
//   Lights one diagonal line per layer, rotating through layers.
void diagonal3DRotation() {
  // For each layer index i = 0..3
  for (int i = 0; i < 4; i++) {
    // For each of the 4 LEDs along the “diagonal” of layer i
    for (int j = 0; j < 4; j++) {
      int colIndex = j * 4 + (i % 4);  // maps to [0,5,10,15] when i=0, etc.

      // 1) Ensure this layer and column are off
      digitalWrite(columnPins[colIndex], LOW);
      digitalWrite(layerPins[i], LOW);

      // 2) Activate layer i
      digitalWrite(layerPins[i], HIGH);

      // 3) Light the diagonal LED at (layer i, column colIndex)
      digitalWrite(columnPins[colIndex], HIGH);

      // 4) Hold on
      delay(ON_TIME);

      // 5) Turn it off
      digitalWrite(columnPins[colIndex], LOW);
      digitalWrite(layerPins[i], LOW);

      // 6) Small gap before next LED
      delay(STEP_GAP);
    }
  }
}
