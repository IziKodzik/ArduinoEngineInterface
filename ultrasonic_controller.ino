

int dirPin = 2;
int stepPin = 3;
int trigPin = 4;
int echoPin = 5;
bool dir = 0; // right spin with 0
long duration;
int distance;
int scans[200];

void setup() {
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, 0);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(dirPin, dir);
  Serial.begin(9600);
}
void loop() {
//  scan360();
  for(int i = 0 ; i < 200; ++i)
    motorStep();
  changeDir();
  delay(1000);
  for(int i = 0 ; i < 200; ++i)
    motorStep();
  delay(1000);
  changeDir();  
}

void scan360(){
  for(int i = 0; i < 200; ++i){
    scans[i] = rayCheck();
    motorStep(8,1000);
    delay(200);
  }
  for(int i = 0 ; i < 200; ++i){
    Serial.print(scans[i]);
    Serial.print(" with angle: ");
    Serial.println(i * 1.8);
  }
}
void motorStep(){
  motorStep(8,500);
}
void motorStep(int part, int fDelay,int sDelay){
  for(int i = 0; i < part; ++i){
    digitalWrite(stepPin, 1);
    delayMicroseconds(fDelay);
    digitalWrite(stepPin, 0);
    delayMicroseconds(sDelay);
  }
}

void motorStep(int part,int stepDelay){
  motorStep(part, stepDelay, stepDelay);
}

void changeDir(){
  dir = !dir;
  digitalWrite(dirPin, dir);
}

int rayCheck(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  return distance;
}
