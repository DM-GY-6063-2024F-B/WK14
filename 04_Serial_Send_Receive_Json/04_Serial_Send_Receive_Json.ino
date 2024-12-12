// Using: ArduinoJson by Benoit Blanchon
// v6.21.5
#include <ArduinoJson.h>

int a0Val;
int a0Min;
int a0Max;

void sendData() {
  StaticJsonDocument<128> mJson;
  // JsonObject data = mJson.createNestedObject("data");

  mJson["value"] = a0Val;
  mJson["min"] = a0Min;
  mJson["max"] = a0Max;

  String jsonTextTx = "";
  serializeJson(mJson, jsonTextTx);

  Serial.println(jsonTextTx);
}

void receiveData(const char* jsonText) {
  StaticJsonDocument<128> mJson;
  DeserializationError error = deserializeJson(mJson, jsonText);

  if (error) {
    Serial.println(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  int x = mJson["x"];
  int y = mJson["y"];
  int w = mJson["w"];
  int h = mJson["h"];

  int xVal = map(x, 0, w, 0, 255);
  int yVal = map(y, 0, h, 0, 255);

  analogWrite(2, xVal);
  analogWrite(3, yVal);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  analogWrite(2, 0);
  analogWrite(3, 0);
}

void loop() {
  a0Val = analogRead(A0);
  a0Min = min(a0Min, a0Val);
  a0Max = max(a0Max, a0Val);

  if (Serial.available() > 0) {
    int byteIn = Serial.read();
    if (byteIn == 'G') {
      Serial.flush();
      sendData();
    } else if (byteIn == 'P') {
      String inString = Serial.readStringUntil('\n');
      receiveData(inString.c_str());
    }
  }
  delay(2);
}
