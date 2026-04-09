const int swPin = 3; //3:ConnectorA 4:ConnectorB
const int vibPin = 4; //3:ConnectorA 4:ConnectorB

bool swState = 0;

void setup() {
  Serial.begin(115200);
  pinMode(swPin, INPUT);
  pinMode(vibPin, OUTPUT);
}

void loop() {
  
    if (digitalRead(swPin) == HIGH) {
    swState = !swState;
  }

  if(swState == 1){
    Serial.println("ON");
    digitalWrite(vibPin, HIGH);
    delay(500);
  } else {
    Serial.println("OFF"); 
    digitalWrite(vibPin, LOW);
    delay(500);  
  }

}
