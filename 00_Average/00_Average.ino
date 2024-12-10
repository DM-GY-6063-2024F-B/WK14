int lastSend;

int AVGSIZE = 16;
int value[16];
int avgIdx;

void setup() {
  Serial.begin(9600);
  lastSend = 0;

  for (int i = 0; i < AVGSIZE; i++) {
    value[i] = 0;
  }
  avgIdx = 0;
}

void loop() {
  int a0Val = analogRead(A0);

  // add value to array of last 16 sensor readings
  value[avgIdx] = a0Val;

  // update idx for next reading. make sure it wraps back to 0 with modulos.
  avgIdx = (avgIdx + 1) % AVGSIZE;

  // calculate sum of all values in array
  int valueSum = 0;
  for (int i = 0; i < AVGSIZE; i++) {
    valueSum += value[i];
  }

  // calculate average value
  int valueAvg = valueSum / AVGSIZE;

  // send average value
  if (millis() - lastSend > 50) {
    Serial.println(valueAvg);
    lastSend = millis();
  }

  delay(2);
}
