/*  Roulette Lights – Same spin timing as original, Idle=All ON, Winner hold 10s or button
   Pins:
   D6  -> Lamp 1 (Gate MOSFET)
   D9  -> Lamp 2
   D10 -> Lamp 3
   D5  -> Button NO -> GND  (INPUT_PULLUP)
*/

const int L1 = 6;
const int L2 = 9;
const int L3 = 10;
const int BTN = 5;
const int LAMPS[3] = {L1, L2, L3};

const unsigned long WINNER_HOLD_MS = 10000; // עד 10 שניות או לחיצה

// === אותו פרופיל זמן כמו בקוד המקורי שלך ===
int   stepsMin = 32;
int   stepsMax = 64;
int   dStartMs = 45;
int   dMinMs   = 20;
int   accelPct = 30;
int   easePct  = 60;

// דיבאונס לכפתור
bool lastBtn = HIGH, stableBtn = HIGH;
unsigned long lastChange = 0;
const unsigned long debounceMs = 35;

bool spinning = false;

void allOff() { for (int i=0;i<3;i++) digitalWrite(LAMPS[i], LOW); }
void allOn()  { for (int i=0;i<3;i++) digitalWrite(LAMPS[i], HIGH); }

// ממתין עד ms או עד לחיצה (מחזיר true אם לחצו)
bool waitOrButton(unsigned long ms) {
  unsigned long start = millis();
  bool prev = digitalRead(BTN);
  while (millis() - start < ms) {
    bool r = digitalRead(BTN);
    if (r != prev) {           // שינוי
      delay(5);                // דיבאונס קצר
      if (digitalRead(BTN) == LOW) return true; // לחיצה
      prev = r;
    }
    delay(1);
  }
  return false;
}

void spinAndStop() {
  spinning = true;

  int steps = random(stepsMin, stepsMax + 1);
  int pos   = 0;
  int d     = dStartMs;

  int accelEnd  = (steps * accelPct) / 100;
  int easeStart = (steps * easePct)  / 100;

  for (int i = 0; i < steps; i++) {
    // הדלק הנוכחית, כבה אחרות
    for (int k=0;k<3;k++) digitalWrite(LAMPS[k], k==pos ? HIGH : LOW);

    delay(d);
    pos = (pos + 1) % 3;

    // האצה → בינוני → האטה (כמו בקוד המקורי)
    if (i < accelEnd) {
      if (d > dMinMs) d -= 2;
    } else if (i < easeStart) {
      d += 3;
    } else {
      d += 15;
    }
  }

  // מנורה זוכה
  int winner = (pos + 2) % 3;
  for (int k=0;k<3;k++) digitalWrite(LAMPS[k], k==winner ? HIGH : LOW);

  // החזקת זוכה עד 10s או לחיצה
  (void)waitOrButton(WINNER_HOLD_MS);

  // חזרה למצב רגיל – הכול דולק
  allOn();
  spinning = false;
}

void setup() {
  for (int i=0;i<3;i++) {
    pinMode(LAMPS[i], OUTPUT);
    digitalWrite(LAMPS[i], LOW);
  }
  pinMode(BTN, INPUT_PULLUP);

  // במצב רגיל: כל המנורות דולקות
  allOn();

  randomSeed(analogRead(A0));
}

void loop() {
  bool reading = digitalRead(BTN);
  if (reading != lastBtn) lastChange = millis();

  if (millis() - lastChange > debounceMs) {
    if (stableBtn == HIGH && reading == LOW && !spinning) {
      spinAndStop();
    }
    stableBtn = reading;
  }
  lastBtn = reading;
}
