// 4×4×4 LED Cube – diagonal Move

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
diagonalMove();
  delay(10);
}

// 🔺 Diagonal Move Animation (Common‑Cathode w/ NPN Low‑Side)
//   – Moves a single diagonal dot across each layer in turn.

void diagonalMove() {
  const int STEP_DELAY = 100;  // ms each LED stays lit
  const int LAYER_DELAY = 50;  // ms gap between layers

  // 1) Ensure all layers off & all columns off
  for (int ll = 0; ll < 4; ll++)   digitalWrite(layerPins[ll], LOW);
  for (int c  = 0; c  < 16; c++)   digitalWrite(columnPins[c], LOW);

  // 2) For each layer 0→3
  for (int i = 0; i < 4; i++) {
    // Activate layer i
    digitalWrite(layerPins[i], HIGH);

    // Move a dot along the diagonal (0,5,10,15)
    for (int j = 0; j < 4; j++) {
      int idx = j * 4 + j;    // indices 0,5,10,15
      digitalWrite(columnPins[idx], HIGH);
      delay(STEP_DELAY);
      digitalWrite(columnPins[idx], LOW);
    }

    // Deactivate layer i
    digitalWrite(layerPins[i], LOW);

    // Small gap before next layer
    delay(LAYER_DELAY);
  }
}
