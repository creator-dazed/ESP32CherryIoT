#include <ESP32Servo.h> //ESP32Servo by Kevin Harrington

const int trigPin = 3; //3:ConnectorA 4:ConnectorB
const int echoPin = 1; //1:ConnectorA 5:ConnectorB
const int motorPin = 4; //3:ConnectorA 4:ConnectorB

int angle = 0;
Servo myservo;

float Duration = 0;
float Distance = 0;
  
void setup() {
  Serial.begin(115200);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  myservo.attach(motorPin);
}

void loop() {
    
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  Duration = pulseIn(echoPin, HIGH);
  Duration = Duration/2;
  Distance = Duration*340*100/1000000;
  
  Serial.println(Distance);
 
if (Distance < 20){
    for(angle; angle <= 180; angle++) {                        
    myservo.write(angle);
    delay(20);
  }
  delay(300); 
  
  } else {
  for(angle; angle >= 0; angle--) {                 
    myservo.write(angle);  
    delay(20);
}
  delay(300);
}
}