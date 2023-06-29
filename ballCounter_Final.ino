const int sensorPin = 0;
const int ballThreshold = 50;

int ballCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  if (sensorValue > ballThreshold) {
    ballCount++;
    Serial.println("a");
    delay(500);
  }
}

