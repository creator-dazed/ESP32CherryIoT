const int trigPin = 3; //3:ConnectorA 4:ConnectorB
const int echoPin = 1; //1:ConnectorA 5:ConnectorB
const int motorPin = 4; //3:ConnectorA 4:ConnectorB

float Duration = 0; //Received Interval Time
float Distance = 0; //Calculation results from Duration

//セットアップ
void setup() {
  Serial.begin(115200);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
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

  Serial.print("Distance(距離):");
  Serial.print(Distance);
  Serial.println("cm");

  if (Distance < 5) { 
    //センサーが反応している間だけモーターをオン
    Serial.println("Motor: ON");
    digitalWrite(motorPin, HIGH);
    } else {
      //センサーが反応しなくなったらモーターをオフ
      Serial.println("Motor: OFF");
      digitalWrite(motorPin, LOW); 
      delay(2000);
      } 
      
      //モーターの停止 
      delay(100);
  }