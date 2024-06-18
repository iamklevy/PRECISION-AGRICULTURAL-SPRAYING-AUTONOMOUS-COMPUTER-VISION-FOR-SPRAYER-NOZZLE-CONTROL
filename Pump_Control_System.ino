#define BLYNK_TEMPLATE_ID "TMPL2EXmyJg8X"
#define BLYNK_TEMPLATE_NAME "pump control system"
#define BLYNK_AUTH_TOKEN "sXXVkHT2V59S-RTxLUFBHEhoy_2x0_0H"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "SSID";
char pass[] = "password";

const int pumpPins[4][2] = {
  { 2, 3 },  // Pump 1 IN1 and EN1 on L298N Motor Driver 1
  { 4, 5 },  // Pump 2 IN3 and EN2 on L298N Motor Driver 1
  { 7, 6 },  // Pump 3 IN1 and EN1 on L298N Motor Driver 2
  { 8, 9 }   // Pump 4 IN3 and EN2 on L298N Motor Driver 2
};

const int numRows = 5;
const int numCols = 4;

int pumpStates[numRows][numCols] = {
  { 1, 1, 1, 1 },
  { 1, 1, 1, 1 },
  { 1, 1, 1, 1 },
  { 1, 1, 1, 1 },
  { 1, 1, 1, 1 }
};

BLYNK_WRITE(V1) {  //pump speed
  int speed = param.asInt();
  analogWrite(pumpPins[0][1], speed);
  analogWrite(pumpPins[1][1], speed);
  analogWrite(pumpPins[2][1], speed);
  analogWrite(pumpPins[3][1], speed);
}

BLYNK_WRITE(V2) {  //pump 1 on/off
  int state = param.asInt();
  digitalWrite(pumpPins[0][0], state);
  analogWrite(pumpPins[0][1], 180);
}

BLYNK_WRITE(V3) {  //pump 2 on/off
  int state = param.asInt();
  digitalWrite(pumpPins[1][0], state);
  analogWrite(pumpPins[1][1], 180);
}

BLYNK_WRITE(V4) {  //pump 3 on/off
  int state = param.asInt();
  digitalWrite(pumpPins[2][0], state);
  analogWrite(pumpPins[2][1], 180);
}

BLYNK_WRITE(V5) {  //pump 4 on/off
  int state = param.asInt();
  digitalWrite(pumpPins[3][0], state);
  analogWrite(pumpPins[3][1], 180);
}

void setup() {
  // setting IN & EN pins output
  for (int i = 0; i < numCols; i++) {
    pinMode(pumpPins[i][0], OUTPUT);
    pinMode(pumpPins[i][1], OUTPUT);
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Switching to autopilot mode.");
    autopilot();
  } else {
    Blynk.run();
  }
}

void autopilot() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pumpPins[i][0], HIGH);  // Turn on the pump
    analogWrite(pumpPins[i][1], 180);    // Set the PWM to 180
  }
}
