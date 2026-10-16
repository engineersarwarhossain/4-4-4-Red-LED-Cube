// 4×4×4 LED Cube – Layer Climb Botom To Top

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
  digitalWrite(layerPins[l],LOW);
  }
}

void loop() {
expandContract();
  delay(10);
}

// 🔄 Expand & Contract Animation (Common‑Cathode w/ NPN Low‑Side)
//   – Lights all LEDs in a layer, one layer at a time, then turns them off.

void expandContract() {
  const int ON_TIME       = 200;  // ms to hold the full layer on
  const int LAYER_GAP     = 100;  // ms between layers

  // For each layer 0→3
  for (int l = 0; l < 4; l++) {
    // 1) Ensure all layers off & all columns off
    for (int ll = 0; ll < 4; ll++)   digitalWrite(layerPins[ll], LOW);
    for (int c  = 0; c  < 16; c++)   digitalWrite(columnPins[c], LOW);

    // 2) Activate layer l
    digitalWrite(layerPins[l], HIGH);

    // 3) Turn on every column (fills the layer)
    for (int c = 0; c < 16; c++) {
      digitalWrite(columnPins[c], HIGH);
    }

    // 4) Hold full layer on
    delay(ON_TIME);

    // 5) Turn off every column (empties the layer)
    for (int c = 0; c < 16; c++) {
      digitalWrite(columnPins[c], LOW);
    }

    // 6) Deactivate layer l
    digitalWrite(layerPins[l], LOW);

    // 7) Pause before next layer
    delay(LAYER_GAP);
  }
}
