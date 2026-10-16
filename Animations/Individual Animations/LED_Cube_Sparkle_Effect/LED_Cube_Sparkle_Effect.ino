// 4×4×4 LED Cube – sparkle Effect

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
randomSeed(analogRead(A5));  // seed RNG
}

void loop() {
  sparkleEffect();
  delay(10);
}

// ✨ Sparkle Effect (Common‑Cathode w/ NPN Low‑Side)
//   – Random single‑LED flashes (“sparkles”) throughout the cube.

void sparkleEffect() {
  const int SPARKLES = 40;   // total random flashes
  const int ON_TIME   = 10;  // ms each sparkle stays lit

  for (int i = 0; i < SPARKLES; i++) {
    // 1) Clear all layers & columns
    for (int ll = 0; ll < 4; ll++)   digitalWrite(layerPins[ll], LOW);
    for (int cc = 0; cc < 16; cc++)  digitalWrite(columnPins[cc], LOW);

    // 2) Pick a random layer 0–3 and column 0–15
    int l = random(0, 4);
    int c = random(0, 16);

    // 3) Light that single LED
    digitalWrite(layerPins[l], HIGH);    // turn layer l on
    digitalWrite(columnPins[c], HIGH);   // turn column c on
    delay(ON_TIME);

    // 4) Turn it off
    digitalWrite(columnPins[c], LOW);
    digitalWrite(layerPins[l], LOW);

    // (optional) tiny gap before next sparkle
    delay(20);
  }
}
