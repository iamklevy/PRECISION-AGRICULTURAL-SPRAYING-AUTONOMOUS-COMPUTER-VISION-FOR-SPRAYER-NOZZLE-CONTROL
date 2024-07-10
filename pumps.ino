#define p1 10
#define p2 11
#define p3 12
#define p4 13
#define trigger A5

const int arr[4] = { p1, p2, p3, p4 };

char Incoming_value = 0;

const int pumpPins[4][2] = {
  { 2, 3 },  // Pump 1 IN1 and EN1 on L298N Motor Driver 1
  { 4, 5 },  // Pump 2 IN3 and EN2 on L298N Motor Driver 1
  { 7, 6 },  // Pump 3 IN1 and EN1 on L298N Motor Driver 2
  { 8, 9 }   // Pump 4 IN3 and EN2 on L298N Motor Driver 2
};

const int ledPins[4] = { 13, 14, 15, 16 };  // Define LED pins for the pumps

volatile bool newSignal = false;
bool respondToPins = true;

void setup() {
  Serial.begin(9600);
  // setting IN & EN pins output
  for (int i = 0; i < 4; i++) {
    pinMode(pumpPins[i][0], OUTPUT);
    pinMode(pumpPins[i][1], OUTPUT);
  }
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  pinMode(p4, INPUT);
  pinMode(trigger, INPUT);
  attachInterrupt(digitalPinToInterrupt(trigger), handleInterrupt, RISING);
}

void loop() {
  // Read the state of the input pins
  if (respondToPins) {
    int pumpStates[4];
    for (int i = 0; i < 4; i++) {
      pumpStates[i] = digitalRead(arr[i]);
    }

    // Control the pumps based on the state of the input pins
    for (int i = 0; i < 4; i++) {
      controlPumpAndLed(i, pumpStates[i], pumpStates[i] ? 180 : 0);
    }
  }

  if (newSignal || Serial.available() > 0) {
    newSignal = false;  // Reset the flag
    Incoming_value = Serial.read();
    Serial.print(Incoming_value);
    Serial.print("\n");
    if (Incoming_value == '1') {
      respondToPins = false;
      controlPumpAndLed(0, HIGH, 180);
    } else if (Incoming_value == '2') {
      respondToPins = false;
      controlPumpAndLed(1, HIGH, 180);
    } else if (Incoming_value == '3') {
      respondToPins = false;
      controlPumpAndLed(2, HIGH, 180);
    } else if (Incoming_value == '4') {
      respondToPins = false;
      controlPumpAndLed(3, HIGH, 180);
    } else if (Incoming_value == '5') {
      respondToPins = false;
      controlPumpAndLed(0, LOW, 0);
    } else if (Incoming_value == '6') {
      respondToPins = false;
      controlPumpAndLed(1, LOW, 0);
    } else if (Incoming_value == '7') {
      respondToPins = false;
      controlPumpAndLed(2, LOW, 0);
    } else if (Incoming_value == '8') {
      respondToPins = false;
      controlPumpAndLed(3, LOW, 0);
    } else if (Incoming_value == '#') {
      respondToPins = false;
      for (int i = 0; i < 4; i++) {
        analogWrite(pumpPins[i][1], 60);
      }
    } else if (Incoming_value == '$') {
      respondToPins = false;
      for (int i = 0; i < 4; i++) {
        analogWrite(pumpPins[i][1], 180);
      }
    } else if (Incoming_value == '%') {
      respondToPins = false;
      for (int i = 0; i < 4; i++) {
        analogWrite(pumpPins[i][1], 255);
      }
    } else if (Incoming_value == '9') {
      respondToPins = true; // Resume responding to pin states
    }
    else if (Incoming_value == '10') {
      respondToPins = false; // Resume responding to pin states
    }
  }
}

void handleInterrupt() {
  newSignal = true;
}

void controlPumpAndLed(int pumpIndex, int pumpState, int pwmValue) {
  digitalWrite(pumpPins[pumpIndex][0], pumpState); // Control the pump
  analogWrite(pumpPins[pumpIndex][1], pwmValue); // Set the PWM value for the pump
  digitalWrite(ledPins[pumpIndex], pumpState); // Control the LED
}

void autopilot() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pumpPins[i][0], HIGH);  // Turn on all the pumps
    analogWrite(pumpPins[i][1], 180);    // Set the PWM to 180
  }
}
