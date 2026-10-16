// 4×4×4 LED Cube – Rain Effect Only (Common‑Cathode w/ NPN Low‑Side)

// == Pin Definitions ==
const int columnPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, 0,  1
};
const int layerPins[4] = { 2, 3, 4, 5 };  // NPN transistor bases

// == Timing ==
const int DROP_DELAY   = 10;  // ms each drop step
const int BETWEEN_DROPS = 200; // ms between individual drops
const int CYCLE_DELAY   = 500; // ms before starting a new rain cycle

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
  randomSeed(analogRead(A5));  // seed the RNG
}

void loop() {
  rainEffect();
  delay(CYCLE_DELAY);
}

// ☔ Rain Effect (Common‑Cathode w/ NPN Low‑Side)
// Simulates a rain drop “falling” down a random column.
void rainEffect() {
  const int CYCLES        = 20;   // মোট ২০ বার ড্রপ গ্রুপ
  const int DROP_DELAY    = 100;  // ms প্রতি স্তর ধরে রাখবে
  const int BETWEEN_GROUP = 200;  // ms প্রতিটি গ্রুপের মাঝে বিরতি

  for (int cycle = 0; cycle < CYCLES; cycle++) {
    // ১) গ্রুপের জন্য 1 থেকে 4 ফোটা নির্ধারণ
    int groupSize = random(1, 5);    // 1,2,3 বা 4

    // ২) ভিন্ন ভিন্ন কলাম নম্বর বেছে নেওয়া
    int cols[4];
    int count = 0;
    while (count < groupSize) {
      int c = random(0, 16);
      // চেক করে নাও আগে এড হয়েছে কিনা
      bool exists = false;
      for (int k = 0; k < count; k++) {
        if (cols[k] == c) { exists = true; break; }
      }
      if (!exists) {
        cols[count++] = c;
      }
    }

    // ৩) উপরে থেকে নিচে ফোটা “ড্রপ” দেখানো
    for (int l = 3; l >= 0; l--) {
      // সব OFF
      for (int ll = 0; ll < 4; ll++)   digitalWrite(layerPins[ll], LOW);
      for (int cc = 0; cc < 16; cc++)  digitalWrite(columnPins[cc], LOW);

      // ওই লেয়ার ON
      digitalWrite(layerPins[l], HIGH);

      // গ্রুপের প্রতিটি কলামে LED ON
      for (int i = 0; i < groupSize; i++) {
        digitalWrite(columnPins[ cols[i] ], HIGH);
      }

      // ধরে রাখ
      delay(DROP_DELAY);

      // সব OFF
      for (int i = 0; i < groupSize; i++) {
        digitalWrite(columnPins[ cols[i] ], LOW);
      }
      digitalWrite(layerPins[l], LOW);
    }

    // পরের গ্রুপের আগে বিরতি
    delay(BETWEEN_GROUP);
  }
}
