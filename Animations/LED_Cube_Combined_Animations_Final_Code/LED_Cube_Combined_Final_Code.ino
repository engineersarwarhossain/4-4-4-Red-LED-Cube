// 4×4×4 LED Cube –Final Code

// == Pin Definitions ==
const int columnPins[16] = {
  6,  7,  8,  9,
  10, 11, 12, 13,
  A0, A1, A2, A3,
  A4, A5, 0,  1
};
const int layerPins[4] = { 2, 3, 4, 5 };  // NPN transistor bases via resistors

int animationState = 0;   // 0 to 4 (representing 5 animations)
int loopCounter = 0;      // Counter for animation 5
const int System_delay = 3000;     // Make delay between animations

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
  randomSeed(analogRead(0)); // Optional: for better randomness
}


//##############################################################################################################################################
void loop() {
  switch (animationState) {
    case 0:
      layerSpin();    // 🔃 Layer Spin
      delay(500);     // LayerSpin CYCLE_GAP_1
     loopCounter++;
      if (loopCounter >= 4) {
      animationState++;  
      }
      break;
    case 1:
      expandContract();
      delay(50);
      expandContract();
      delay(50);
      expandContract();
      delay(50);
      expandContract();
      delay(50);
      animationState++;
      loopCounter = 0;  // Reset counter before animation 3
      break;
    case 2:
      Spairal_Effect();
      delay(50);
      loopCounter++;
      if (loopCounter >= 4) {
      animationState++;  
      }
      break;
    case 3:
      refreshmentAnimation();   //🔄 Refreshment Animation
      delay(500);  // pause before repeating
      refreshmentAnimation();   //🔄 Refreshment Animation
      delay(500);
      animationState++;
      loopCounter = 0;  // Reset counter before animation 5
      break;
    case 4:
      Smooth_Animation();
      loopCounter++;
      if (loopCounter >= 1500) {// loopCounter >=1000
      animationState++;  
      }
      break;
    case 5:
      Smooth_Animation();
      delay(50);
      Vortex_Effect();
      delay(50);
      Vortex_Effect();
      delay(50);
      Vortex_Effect();
      delay(50);
      animationState++;
      loopCounter = 0;  // Reset counter before animation 7
      break;
    case 6:
      Unifide_Axis_Plane_Sweep_Animation();
      delay(50);
      loopCounter++;
      if (loopCounter >= 4) {
      animationState++;  
      }
      break;
    case 7:
      crossRotation();
      delay(50);
      crossRotation();
      delay(50);
      crossRotation();
      delay(50);
      crossRotation();
      delay(50);
      animationState++;
      loopCounter = 0;  // Reset counter before animation 9
      break;
    case 8:
      diagonal3DRotation();
      delay(50);
      loopCounter++;
      if (loopCounter >= 4) {
      animationState++;  
      }
      break;
    case 9:
      diagonalMove();
      delay(50);
      diagonalMove();
      delay(50);
      diagonalMove();
      delay(50);
      diagonalMove();
      delay(50);
      animationState++;
      loopCounter = 0;  // Reset counter before animation 11
      break;
    case 10:
      diagonalMoveSequential();
      delay(50);
      loopCounter++;
      if (loopCounter >= 4) {
      animationState++;  
      }
      break;
    case 11:
      waveAnimation();
      delay(50);
      waveAnimation();
      delay(50);
      waveAnimation();
      delay(50);
      waveAnimation();
      delay(50);
      animationState ++;
      loopCounter = 0;  // Reset counter before animation 13
      break;
    case 12:
      Heartbeat_animation();
      loopCounter++;
      if (loopCounter >= 1000) {// loopCounter >=1000
      animationState++;  
      }
      break;
    case 13:
      circularWave(); //there is some Problem
      delay(10);
      circularWave(); //there is some Problem
      delay(10);
      circularWave(); //there is some Problem
      delay(10);
      circularWave(); //there is some Problem
      delay(10);
      animationState++;
      loopCounter = 0;  // Reset counter before animation 15
      break;
    case 14:
      randomBlink(); //there is some Problem
      delay(50);
      loopCounter++;
      if (loopCounter >= 50) {// loopCounter >=1000
      animationState++;  
      }
      break;
    case 15:
      sparkleEffect(); //there is some Problem
      delay(10);
      animationState++;
      loopCounter = 0;  // Reset counter before animation 17
      break;
    case 16:
      rainEffect();
      delay(50); // ms before starting a new rain cycle
      loopCounter++;
      if (loopCounter >= 1000) {// loopCounter >=1000
      animationState = 0;  // Start from animation1 again 
      }
      break;
  }
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

// == Timing for Layer Spin ==
const int ON_TIME_1   = 100;  // ms each sub‑step holds 
const int STEP_GAP_1  = 100;  // ms between each layer step
const int CYCLE_GAP_1 = 500;  // ms between full spin cycles 
//Also SET CYCLE_GAP_1 in Void Loop

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
      delay(ON_TIME_1);

      // 5) Turn everything off
      for (int c = 0; c < 16; c++)      digitalWrite(columnPins[c], LOW);
      digitalWrite(layerPins[l], LOW);

      // 6) Small gap before next layer
      delay(STEP_GAP_1);
    }
  }
}


// 🔄 Layer Climb Botom To Top Animation (Common‑Cathode w/ NPN Low‑Side)
//   – Lights all LEDs in a layer, one layer at a time, then turns them off.

void expandContract() {
  const int ON_TIME_2       = 200;  // ms to hold the full layer on
  const int LAYER_GAP_2     = 100;  // ms between layers

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
    delay(ON_TIME_2);

    // 5) Turn off every column (empties the layer)
    for (int c = 0; c < 16; c++) {
      digitalWrite(columnPins[c], LOW);
    }

    // 6) Deactivate layer l
    digitalWrite(layerPins[l], LOW);

    // 7) Pause before next layer
    delay(LAYER_GAP_2);
  }
}

void Spairal_Effect() {

  // == Timing ==
const int ON_TIME       = 50;   // ms each LED is lit
const int GAP_BETWEEN   = 300;  // ms between each stackSize step
const int GAP_SEQUENCE  = 500;  // ms between full up‑and‑down cycle


  // Sequence: 1→2→3→4→3→2→1→0 layers on
  const int stackSeq[] = { 1, 2, 3, 4, 3, 2, 1, 0 };
  const int steps = sizeof(stackSeq) / sizeof(stackSeq[0]);

  // Spiral ordering for the 4×4 plane
  const int spiralOrder[16] = {
     12,  8,  4,  0,
    1, 5, 9, 13,
     14,  10,  6,  2,
    3, 7,  11,  15
  };

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
      int col = spiralOrder[i];
      digitalWrite(columnPins[col], HIGH);
      delay(ON_TIME);
      digitalWrite(columnPins[col], LOW);
    }

    // 4) Pause before next stackSize
    delay(GAP_BETWEEN);
  }

  // Full cycle done: brief pause then repeat
  delay(GAP_SEQUENCE);
}



// 🔄 Refreshment Animation (Common‑Cathode w/ NPN Low‑Side)
//   – LEDs fill from layer 0→3, hold 4 s, then empty from 3→0

void refreshmentAnimation() {
  const int FILL_STEP_DELAY  = 500;   // ms between lighting each layer
  const int HOLD_TIME        = 3000;  // ms to hold all LEDs on
  const int EMPTY_STEP_DELAY = 500;   // ms between turning each layer off

  // 1) Clear everything
  for (int c = 0; c < 16; c++) digitalWrite(columnPins[c], LOW);
  for (int l = 0; l < 4;  l++) digitalWrite(layerPins[l],  LOW);

  // 2) Fill from bottom (layer 0) to top (layer 3)
  for (int l = 0; l < 4; l++) {
    digitalWrite(layerPins[l], HIGH);        // turn layer l on
    for (int c = 0; c < 16; c++)             // turn all columns on
      digitalWrite(columnPins[c], HIGH);
    delay(FILL_STEP_DELAY);
  }

  // 3) Hold all LEDs lit
  delay(HOLD_TIME);

  // 4) Empty from top (layer 3) down to bottom (layer 0)
  for (int l = 3; l >= 0; l--) {
    digitalWrite(layerPins[l], LOW);         // turn layer l off
    delay(EMPTY_STEP_DELAY);
  }

  // 5) Finally clear all columns as well
  for (int c = 0; c < 16; c++) digitalWrite(columnPins[c], LOW);
}


// 4×4×4 LED Cube: Smooth Global Glow Animation

void drawFrame(float brightness) {
  // Pin definitions
const uint8_t layerPins[4] = {2, 3, 4, 5};      // Common cathodes (z=0..3)
const uint8_t colPins[16]  = {6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5, 0, 1};

// PWM timing (microseconds per layer cycle)
const uint32_t PWM_PERIOD = 2000;

  uint32_t onTime = PWM_PERIOD * brightness;
  uint32_t offTime = PWM_PERIOD - onTime;
  for (uint8_t z = 0; z < 4; z++) {
    for (uint8_t c = 0; c < 16; c++) {
    digitalWrite(colPins[c], HIGH); 
    }
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(onTime);
    digitalWrite(layerPins[z], LOW);
    delayMicroseconds(offTime);
  }
}

void Smooth_Animation() {
// Glow parameter settings (edit in code):
// BASE_BRIGHTNESS: minimum brightness (0.0 off to 1.0 full)
// AMPLITUDE: extra brightness swing (0.0 none to 1.0 full)
// SPEED_RATE: phase increment per loop (controls speed)
const float BASE_BRIGHTNESS = 0.0f;
const float AMPLITUDE       = 1.0f;
const float SPEED_RATE      = 0.05f;

  static float phase = 0;
  float b = BASE_BRIGHTNESS + AMPLITUDE * (0.5f + 0.5f * sin(phase));
  b = constrain(b, 0.0f, 1.0f);
  drawFrame(b);
  phase += SPEED_RATE;
}



// 4×4×4 LED Cube – Layer Stack Vortex Pattern (Common‑Cathode w/ NPN Low‑Side)
// 🔄 Vortex Effect
void Vortex_Effect() {
  // Sequence: 1→2→3→4→3→2→1→0 layers on
  const int stackSeq[] = { 1, 2, 3, 4, 3, 2, 1, 0 };
  const int steps = sizeof(stackSeq) / sizeof(stackSeq[0]);

// Spiral ordering for the 4×4 plane if needed!

// == Timing ==
const int ON_TIME       = 30;   // ms each LED is lit
const int GAP_BETWEEN   = 100;  // ms between each stackSize step
const int GAP_SEQUENCE  = 500;  // ms between full up‑and‑down cycle

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


// 4×4×4 LED Cube: Unified Axis Plane Sweep Animation
// Speed controlled by constants in code

uint16_t cubeData[4]; // per-layer 16-bit masks

// Helper: clear all voxels
void clearCube() {
  for (uint8_t z = 0; z < 4; z++) cubeData[z] = 0;
}

// Helper: set one voxel
void setVoxel(uint8_t x, uint8_t y, uint8_t z, bool on) {
  if (x > 3 || y > 3 || z > 3) return;
  uint8_t bit = y * 4 + x;
  if (on) cubeData[z] |=  (1 << bit);
  else    cubeData[z] &= ~(1 << bit);
}

// Helper: multiplex and draw one frame
// next line structure void drawCubeFrame(uint16_t dwellUs = PWM_PERIOD) {
void drawCubeFrame(uint16_t dwellUs = 1000) {
   // Brightness control (0.0 = off, 1.0 = full brightness)
const float BRIGHTNESS = 1.0f;     // Set global brightness here

  uint32_t onTime  = (uint32_t)(dwellUs * BRIGHTNESS);
  uint32_t offTime = dwellUs - onTime;

  for (uint8_t z = 0; z < 4; z++) {
    for (uint8_t i = 0; i < 16; i++) {
      digitalWrite(columnPins[i], (cubeData[z] & (1 << i)) ? HIGH : LOW);
      
    }
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(dwellUs);
    digitalWrite(layerPins[z], LOW);
  }
}

// Unified plane sweep along any axis
// axis: 'X', 'Y', or 'Z'
// repeat: number of full cycles
// delayMs: pause per plane (controls animation speed)
void animPlaneSweepAll(char axis, uint8_t repeat, uint16_t delayMs) {
  for (uint8_t r = 0; r < repeat; r++) {
    if (axis == 'X') {
      for (uint8_t x = 0; x < 4; x++) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
      for (int8_t x = 2; x >= 0; x--) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
    } else if (axis == 'Y') {
      for (uint8_t y = 0; y < 4; y++) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t x = 0; x < 4; x++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
      for (int8_t y = 2; y >= 0; y--) {
        clearCube();
        for (uint8_t z = 0; z < 4; z++)
          for (uint8_t x = 0; x < 4; x++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
    } else if (axis == 'Z') {
      for (uint8_t z = 0; z < 4; z++) {
        clearCube();
        for (uint8_t x = 0; x < 4; x++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
      for (int8_t z = 2; z >= 0; z--) {
        clearCube();
        for (uint8_t x = 0; x < 4; x++)
          for (uint8_t y = 0; y < 4; y++) setVoxel(x, y, z, true);
        drawCubeFrame();
        delay(delayMs);
      }
    }
  }
}

void Unifide_Axis_Plane_Sweep_Animation() {

// Animation speed settings (ms pause per plane)
  //To Change Animation Speed Change the Constant Values
const uint16_t speedDelayX = 100;
const uint16_t speedDelayY = 150;
const uint16_t speedDelayZ = 200;

  // Change animation Repetation by adjusting these constants above
  animPlaneSweepAll('X', 2, speedDelayX);
  delay(200);
  animPlaneSweepAll('Y', 2, speedDelayY);
  delay(200);
  animPlaneSweepAll('Z', 2, speedDelayZ);
  delay(1000);
}




// 4×4×4 LED Cube – Cross Rotation Only (Common‑Cathode w/ NPN Low‑Side)
void crossRotation() {

  // == Timing ==
const int ON_TIME   = 300;  // ms each “cross” stays lit
const int LAYER_GAP = 100;  // ms between layers

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





// 🔺 3D Diagonal Rotation (Common‑Cathode w/ NPN Low‑Side)
//   Lights one diagonal line per layer, rotating through layers.
void diagonal3DRotation() {

  
// == Timing ==
const int ON_TIME   = 100;  // ms LED on per step
const int STEP_GAP  = 50;   // ms gap between steps
const int CYCLE_GAP = 500;  // ms pause after full rotation

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






// 🌊 Wave Animation (Common‑Cathode w/ NPN Low‑Side)
// Lights each column in turn on each layer, creating a “wave” up the cube.
void waveAnimation() {

  // == Timing ==
const int STEP_DELAY = 50;   // ms each LED stays lit
const int LAYER_DELAY = 100; // ms between layers
const int CYCLE_DELAY = 500; // ms between full cycles

  for (int l = 0; l < 4; l++) {
    // 1) Clear all columns and layers
    for (int c = 0; c < 16; c++)      digitalWrite(columnPins[c], LOW);
    for (int ll = 0; ll < 4; ll++)    digitalWrite(layerPins[ll], LOW);

    // 2) Activate only layer l
    digitalWrite(layerPins[l], HIGH);

    // 3) Sweep through all 16 columns
    for (int c = 0; c < 16; c++) {
      digitalWrite(columnPins[c], HIGH);
      delay(STEP_DELAY);
      digitalWrite(columnPins[c], LOW);
    }

    // 4) Turn this layer off
    digitalWrite(layerPins[l], LOW);

    // 5) Small gap before next layer
    delay(LAYER_DELAY);
  }
}





// 4×4×4 LED Cube: 3D Heartbeat Pulse Animation

// Compute brightness for heartbeat: two quick peaks per cycle
float heartbeatBrightness(float t) {
// --- Heartbeat Settings ---
  const float BASE_BRIGHTNESS = 0.2f;   // minimum brightness (0.0..1.0)
  const float AMPLITUDE       = 0.8f;   // brightness swing range
  // Create dual peak: sin(t) * sin(t*0.5) yields two pulses
  float beat = sin(t) * sin(t * 0.5f);
  // Normalize to range 0..1
  beat = (beat + 1.0f) * 0.5f;
  // Scale to BASE..BASE+AMPLITUDE
  return BASE_BRIGHTNESS + beat * AMPLITUDE;
}


// Draw one full multiplexed refresh at given brightness
void drawPulseFrame(float brightness) {
// --- Heartbeat Settings ---
  const uint32_t PWM_PERIOD   = 1500;   // microseconds per layer cycle

  uint32_t onTime  = (uint32_t)(PWM_PERIOD * brightness);
  uint32_t offTime = PWM_PERIOD - onTime;
  for (uint8_t z = 0; z < 4; z++) {
    // Turn on all columns
    for (uint8_t c = 0; c < 16; c++) digitalWrite(columnPins[c], HIGH);
    // Activate layer (LOW to sink current)
    digitalWrite(layerPins[z], HIGH);
    delayMicroseconds(onTime);
    // Deactivate layer
    digitalWrite(layerPins[z], LOW);
    delayMicroseconds(offTime);
  }
}


void Heartbeat_animation() {
// --- Heartbeat Settings ---
const float SPEED_RATE      = 0.07f;  // phase increment per loop
static float phase = 0.0f;

  // Calculate dynamic brightness
  float b = heartbeatBrightness(phase);
  b = constrain(b, 0.0f, 1.0f);
  // Refresh cube at brightness b
  drawPulseFrame(b);
  // Advance phase for next frame
  phase += SPEED_RATE;
}





// 🌊 Circular Wave Animation (Common‑Cathode, NPN Transistors)
//     – LEDs light from center outward in concentric square patterns

void circularWave() {
  const int STEP_DELAY = 500;  // time between wave layers (ms)

  // Concentric square LED groups (per 4×4 layer):
  // Center → Mid → Outer ring
  int waveOrder[4][4] = {
    {5, 6, 9, 10},     // Center square
    {1, 7, 14, 8},      // Next out
    {2, 11, 13, 4},   // Next ring
    {0, 3, 12, 15}     // Corners
  };

  // Loop through each ring (center to outer)
  for (int ring = 0; ring < 4; ring++) {
    for (int layer = 0; layer < 4; layer++) {
      digitalWrite(layerPins[layer], HIGH);   // turn on the layer
      for (int i = 0; i < 4; i++) {
        int col = waveOrder[ring][i];
        digitalWrite(columnPins[col], HIGH);  // light all 4 ring LEDs
      }
      delay(STEP_DELAY);
      for (int i = 0; i < 4; i++) {
        digitalWrite(columnPins[waveOrder[ring][i]], LOW);  // off
      }
      digitalWrite(layerPins[layer], LOW);    // layer off
    }
  }
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






// ☔ Rain Effect (Common‑Cathode w/ NPN Low‑Side)
// Simulates a rain drop “falling” down a random column.
void rainEffect() {
  const int CYCLES        = 20;   // মোট ২০ বার ড্রপ গ্রুপ
  const int DROP_DELAY    = 100;  // ms প্রতি স্তর ধরে রাখবে
  const int BETWEEN_GROUP = 200;  // ms প্রতিটি গ্রুপের মাঝে বিরতি
  const int BETWEEN_DROPS = 200; // ms between individual drops

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





