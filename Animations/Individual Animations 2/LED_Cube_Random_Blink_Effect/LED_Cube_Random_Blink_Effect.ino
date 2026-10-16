// 4×4×4 LED Cube – 💡 Random Blink Effect (Common-Cathode, NPN-transistor layers)

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
  randomBlink();
  delay(500);
}
// 💡 Random Blink Effect (Common-Cathode, NPN-transistor layers)
//    – Random LEDs blink ON briefly at random positions in the cube

void randomBlink() {
  const int BLINKS   = 30;    // Total number of random blinks
  const int ON_TIME  = 100;   // How long each LED stays on (ms)

  for (int i = 0; i < BLINKS; i++) {
    // Turn everything OFF
    for (int l = 0; l < 4; l++)   digitalWrite(layerPins[l], LOW);
    for (int c = 0; c < 16; c++)  digitalWrite(columnPins[c], LOW);

    // Pick a random layer and a random column
    int l = random(0, 4);        // Layer 0–3
    int c = random(0, 16);       // Column 0–15

    // Light the selected LED
    digitalWrite(layerPins[l], HIGH);     // Enable layer (NPN base ON)
    digitalWrite(columnPins[c], HIGH);    // Enable column (anode HIGH)

    delay(ON_TIME);

    // Turn off that LED
    digitalWrite(columnPins[c], LOW);
    digitalWrite(layerPins[l], LOW);
  }
}
