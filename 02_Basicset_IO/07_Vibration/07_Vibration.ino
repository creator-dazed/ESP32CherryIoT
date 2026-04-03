const int vibPin = 3; //3:ConnectorA 4:ConnectorB

void setup() {
  pinMode(vibPin, OUTPUT);
}

void loop() {
  digitalWrite(vibPin, HIGH);
  delay(500);
  digitalWrite(vibPin, LOW);
  delay(500);
  digitalWrite(vibPin, HIGH);
  delay(200);
  digitalWrite(vibPin, LOW);
  delay(200);
}
