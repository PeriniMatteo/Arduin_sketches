
int motorPinDirA = 12;
int motorPinDirB = 13;
int motorPinPwmA = 3;
int motorPinPwmB = 11;
int delayTime = 10;

void setup() {
  pinMode(motorPinDirA, OUTPUT);
  pinMode(motorPinDirB, OUTPUT);
  pinMode(motorPinPwmA, OUTPUT);
  pinMode(motorPinPwmB, OUTPUT);
}

 
void loop() {
 
  digitalWrite(motorPinDirA, HIGH);
  digitalWrite(motorPinDirB, LOW);
  digitalWrite(motorPinPwmA, HIGH);
  digitalWrite(motorPinPwmB, LOW);
  delay(delayTime);
  
  digitalWrite(motorPinDirA, HIGH);
  digitalWrite(motorPinDirB, HIGH);
  digitalWrite(motorPinPwmA, HIGH);
  digitalWrite(motorPinPwmB, HIGH);
  delay(delayTime);
 
  digitalWrite(motorPinDirA, LOW);
  digitalWrite(motorPinDirB, HIGH);
  digitalWrite(motorPinPwmA, LOW);
  digitalWrite(motorPinPwmB, HIGH);
  delay(delayTime);
 
  digitalWrite(motorPinDirA, LOW);
  digitalWrite(motorPinDirB, HIGH);
  digitalWrite(motorPinPwmA, HIGH);
  digitalWrite(motorPinPwmB, HIGH);
  delay(delayTime);
 
  digitalWrite(motorPinDirA, LOW);
  digitalWrite(motorPinDirB, LOW);
  digitalWrite(motorPinPwmA, HIGH);
  digitalWrite(motorPinPwmB, LOW);
  delay(delayTime);
   digitalWrite(motorPinDirA, LOW);
  digitalWrite(motorPinDirB, LOW);
  digitalWrite(motorPinPwmA, HIGH);
  digitalWrite(motorPinPwmB, HIGH);
  delay(delayTime);
    digitalWrite(motorPinDirA, LOW);
  digitalWrite(motorPinDirB, LOW);
  digitalWrite(motorPinPwmA, LOW);
  digitalWrite(motorPinPwmB, HIGH);
  delay(delayTime);
      digitalWrite(motorPinDirA, HIGH);
  digitalWrite(motorPinDirB, LOW);
  digitalWrite(motorPinPwmA, HIGH);
  digitalWrite(motorPinPwmB, HIGH);
  delay(delayTime);
}
