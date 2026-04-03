const int ruptPin = 3; //3:ConnectorA 4:ConnectorB

void setup(){
  pinMode(ruptPin, INPUT);
  Serial.begin(115200);
}

void loop(){
  //Look at the serial monitor
  if (digitalRead(ruptPin)==LOW) {
    Serial.println("遮断されました");
  } else {
    Serial.println("正常に作動しています");
  }
  delay(500);
}
