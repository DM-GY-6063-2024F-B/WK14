void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {
  int a0Val = analogRead(A0);

  if (Serial.available() > 0) {
    int byteIn = Serial.read();
    if (byteIn == 'G') {
      Serial.flush();
      Serial.println(a0Val);
    } else if (byteIn == 'P') {
      String inString = Serial.readStringUntil('\n');
      inString.trim();

      int intVal = inString.toInt();
      digitalWrite(2, intVal);
    }
  }
}
