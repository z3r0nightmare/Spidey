//  --------                 --------
// |  D9    |               |  D7    |
// | joint9 |               | joint7 |
//  ----- --------     --------- -----
//       |  D8    |   |  D6    |
//       | joint8 |   | joint6 |
//        --------     --------
//       |  D2    |  |   D4    |
//       | joint2 |  |  joint4 |
//  ----- --------    --------- -----
// |  D3    |               |  D5    |
// | joint3 |               | joint5 |
//  --------                 --------
//                Front



#include <Servo.h>

// ---------- Servo objects ----------
Servo joint2;
Servo joint3;
Servo joint4;
Servo joint5;
Servo joint6;
Servo joint7;
Servo joint8;
Servo joint9;

// ---------- Home positions ----------
const int HOME_13579 = 180; // 3,5,7,9
const int HOME_2468  = 75;  // 2,4,6,8

// ---------- Motion tuning ----------
const int STEP = 2;            // increment per update
const int STEP_DELAY_MS = 10;  // small delay for smooth motion

// ---------- Runtime state ----------
int prog3 = 0, prog5 = 0, prog7 = 0, prog9 = 0;
int dir3 = 1, dir5 = 0, dir7 = 0, dir9 = 0;

// ---------- Duration ----------
const unsigned long MOTION_DURATION = 4000; // 4 seconds per function

void setup() {
  // Attach servos
  joint2.attach(2);
  joint3.attach(3);
  joint4.attach(4);
  joint5.attach(5);
  joint6.attach(6);
  joint7.attach(7);
  joint8.attach(8);
  joint9.attach(9);

  // Move all to home
  goHome();
}

void loop() {
  unsigned long startTime;

  // ---------- TWERK ----------
  prog3 = prog5 = dir3 = 1; dir5 = 0; // reset
  startTime = millis();
  while (millis() - startTime < MOTION_DURATION) {
    twerk(100);
  }

  // ---------- JUMP ----------
  startTime = millis();
  while (millis() - startTime < MOTION_DURATION) {
    jump(120);
  }

  // ---------- HELLO ----------
  startTime = millis();
  while (millis() - startTime < MOTION_DURATION) {
    hello(120, 90);
  }

  // ---------- GO HOME ----------
  goHome();
}

// ----------------- TWERK FUNCTION -----------------
void twerk(int minAngle) {
  int STEPS = HOME_13579 - minAngle;
  int MID_POINT = STEPS / 2;

  // Joint3 (leader)
  updateProg(prog3, dir3, STEPS);
  int angle3 = HOME_13579 - prog3;
  int angle7 = HOME_13579 + minAngle - angle3; // mirrored
  joint3.write(angle3);
  joint7.write(angle7);

  // Trigger Joint5 once Joint3 hits midpoint
  if (dir5 == 0 && prog3 >= MID_POINT) { dir5 = 1; prog5 = 0; }

  // Joint5 & Joint9 motion
  if (dir5 != 0) {
    updateProg(prog5, dir5, STEPS);
    int angle5 = HOME_13579 - prog5;
    int angle9 = HOME_13579 + minAngle - angle5; // mirrored
    joint5.write(angle5);
    joint9.write(angle9);
  }

  delay(STEP_DELAY_MS);
}

// ----------------- JUMP FUNCTION -----------------
void jump(int targetAngle) {
  static int prog = 0;
  static int dir = 1;
  int STEPS = abs(HOME_13579 - targetAngle);

  prog += dir * STEP;
  if (prog >= STEPS) { prog = STEPS; dir = -1; }
  if (prog <= 0) { prog = 0; dir = 1; }

  int angle = HOME_13579 - prog * ((HOME_13579 > targetAngle) ? 1 : -1);

  joint3.write(angle);
  joint5.write(angle);
  joint7.write(angle);
  joint9.write(angle);

  delay(6);
}

// ---------- HELLO FUNCTION ----------
void hello(int joint2Target, int joint3Target) {
  static int prog2 = 0;
  static int dir2 = 1;
  static int prog3_hello = 0;
  static int dir3_hello = 1;

  int STEPS2 = abs(HOME_2468 - joint2Target);
  int STEPS3 = abs(0 - joint3Target);

  // Joint2
  prog2 += dir2 * STEP;
  if (prog2 >= STEPS2) { prog2 = STEPS2; dir2 = -1; }
  if (prog2 <= 0) { prog2 = 0; dir2 = 1; }
  int angle2 = HOME_2468 - prog2 * ((HOME_2468 > joint2Target) ? 1 : -1);
  joint2.write(angle2);

  // Joint3
  prog3_hello += dir3_hello * STEP;
  if (prog3_hello >= STEPS3) { prog3_hello = STEPS3; dir3_hello = -1; }
  if (prog3_hello <= 0) { prog3_hello = 0; dir3_hello = 1; }
  int angle3 = 0 + prog3_hello;
  joint3.write(angle3);

  // Joint7 fixed at 90
  joint7.write(90);

  // Keep other joints at home
  joint5.write(HOME_13579);
  joint9.write(HOME_13579);

  delay(STEP_DELAY_MS);
}

// ----------------- GO HOME FUNCTION -----------------
void goHome() {
  joint2.write(HOME_2468);
  joint3.write(HOME_13579);
  joint4.write(HOME_2468);
  joint5.write(HOME_13579);
  joint6.write(HOME_2468);
  joint7.write(HOME_13579);
  joint8.write(HOME_2468);
  joint9.write(HOME_13579);
  delay(200);
}

// ----------------- Helper function -----------------
void updateProg(int &prog, int &dir, int STEPS) {
  prog += dir * STEP;
  if (prog >= STEPS) { prog = STEPS; dir = -1; }
  if (prog <= 0) { prog = 0; dir = 1; }
}
