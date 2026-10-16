// 4×4×4 LED Cube – Cross Rotation Only (Common‑Cathode w/ NPN Low‑Side)

// == Pin Definitions ==
const int columnPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, 0,  1
};
const int layerPins[4] = { 2, 3, 4, 5 };  // NPN transistor bases

// == Timing ==
const int ON_TIME   = 300;  // ms each “cross” stays lit
const int LAYER_GAP = 100;  // ms between layers

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
  crossRotation();
  delay(500);  // pause before repeating
}

void crossRotation() {
  // For each layer 0→3
  for (int l = 0; l < 4; l++) {
    // 1) Clear ALL columns and layers
    for (int c = 0; c < 16; c++)      digitalWrite(columnPins[c], LOW);
    for (int ll = 0; ll < 4; ll++)    digitalWrite(layerPins[ll], LOW);

    // 2) Turn ON only layer l
    digitalWrite(layerPins[l], HIGH);

    // 3) Light the “cross” edges on that layer:
    //    Top row:    cols 0,1,2,3
    //    Bottom row: cols 12,13,14,15
    //    Left col:   cols 0,4,8,12
    //    Right col:  cols 3,7,11,15
    // (duplicates don’t hurt—just re‑write HIGH)
    for (int i = 0; i < 4; i++) {
      digitalWrite(columnPins[i],         HIGH); // top row
      digitalWrite(columnPins[i + 12],    HIGH); // bottom row
      digitalWrite(columnPins[i * 4],     HIGH); // left column
      digitalWrite(columnPins[i * 4 + 3], HIGH); // right column
    }

    // 4) Hold the pattern
    delay(ON_TIME);

    // 5) Turn everything OFF again
    for (int c = 0; c < 16; c++)      digitalWrite(columnPins[c], LOW);
    digitalWrite(layerPins[l], LOW);

    // 6) Short gap before next layer
    delay(LAYER_GAP);
  }
}
