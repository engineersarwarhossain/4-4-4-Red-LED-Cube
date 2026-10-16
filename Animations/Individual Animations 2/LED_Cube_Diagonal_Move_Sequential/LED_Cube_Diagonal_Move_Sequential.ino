// 4×4×4 LED Cube – diagonal Move Sequential
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
diagonalMoveSequential();
  delay(10);
}

// 🔄 Diagonal Move – One Side at a Time (Common‑Cathode w/ NPN Low‑Side)
//   – First completes the primary diagonal (0→5→10→15) across all layers,
//     then completes the secondary diagonal (3→6→9→12) across all layers.

void diagonalMoveSequential() {
  const int STEP_DELAY = 100;  // ms each LED stays lit
  const int LAYER_DELAY = 50;  // ms gap between layers
  const int SIDE_GAP    = 200; // ms gap between the two diagonal passes

  // Helper: clear all LEDs
  auto clearAll = [&]() {
    for (int c = 0; c < 16; c++)      digitalWrite(columnPins[c], LOW);
    for (int l = 0; l < 4;  l++)      digitalWrite(layerPins[l], LOW);
  };

  // 1) Primary diagonal pass (0,5,10,15)
  for (int layer = 0; layer < 4; layer++) {
    clearAll();
    digitalWrite(layerPins[layer], HIGH);
    for (int j = 0; j < 4; j++) {
      int idx = j * 4 + j;  // 0,5,10,15
      digitalWrite(columnPins[idx], HIGH);
      delay(STEP_DELAY);
      digitalWrite(columnPins[idx], LOW);
    }
    digitalWrite(layerPins[layer], LOW);
    delay(LAYER_DELAY);
  }

  // Small pause before second pass
  delay(SIDE_GAP);

  // 2) Secondary diagonal pass (3,6,9,12)
  for (int layer = 0; layer < 4; layer++) {
    clearAll();
    digitalWrite(layerPins[layer], HIGH);
    for (int j = 0; j < 4; j++) {
      int idx = j * 4 + (3 - j);  // 3,6,9,12
      digitalWrite(columnPins[idx], HIGH);
      delay(STEP_DELAY);
      digitalWrite(columnPins[idx], LOW);
    }
    digitalWrite(layerPins[layer], LOW);
    delay(LAYER_DELAY);
  }

  // Final clear
  clearAll();
}
