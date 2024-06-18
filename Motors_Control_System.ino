#define BLYNK_TEMPLATE_ID "TMPL2yTVDjK7B"
#define BLYNK_TEMPLATE_NAME "motors control system"
#define BLYNK_AUTH_TOKEN "ErmQvrBJiKgkwGizEu7fAGZv4ZkjmAne"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "SSID";
char pass[] = "password";

int IN1 = 4;
int IN2 = 5;
int IN3 = 12;
int IN4 = 13;
int ENA = 18;
int ENB = 19;


BLYNK_WRITE(V1) {  //move forward
  int state = param.asInt();
  Serial.print("Move Forward: ");
  digitalWrite(IN2, state);
  digitalWrite(IN4, state);
}

BLYNK_WRITE(V2) {  //move backward
  int state = param.asInt();
  Serial.print("Move Backward: ");
  digitalWrite(IN1, state);
  digitalWrite(IN3, state);
}

BLYNK_WRITE(V3) {  //turn left
  int state = param.asInt();
  Serial.print("Turn Left: ");
  digitalWrite(IN2, state);
  digitalWrite(IN3, state);
}

BLYNK_WRITE(V4) {  //turn right
  int state = param.asInt();
  Serial.print("Turn Right: ");
  digitalWrite(IN1, state);
  digitalWrite(IN4, state);
}

BLYNK_WRITE(V5) {  //speed accelation
  int speed = param.asInt();
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
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
  Serial.print("Moving Forward on autopilot driving: ");
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
}
