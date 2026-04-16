const int touchPin = 3; //3:ConnectorA 4:ConnectorB
const int vibPin = 4; //3:ConnectorA 4:ConnectorB

bool swState = 0;

void setup() {
  Serial.begin(115200);
  pinMode(touchPin, INPUT);
  pinMode(swPin, OUTPUT);
}

void loop() {
  
  if (digitalRead(touchPin) == HIGH) {
    swState = !swState;
  }

  if(swState == 1){
    Serial.println("ON");
    digitalWrite(spPin, HIGH);
    delay(500);
  } else {
    Serial.println("OFF"); 
    digitalWrite(spPin, LOW);
    delay(500);  
  }

}
