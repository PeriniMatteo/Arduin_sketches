
int motorPinDirA = 12;
int motorPinDirB = 13;
int motorPinPwmA = 3;
int motorPinPwmB = 11;
int delayTime = 20;
int dir=1;
int nStep=0;
int vel;
boolean PwmA[8] = {1,1,1,0,1,1,1,0};
boolean PwmB[8] = {1,0,1,1,1,0,1,1};
boolean DirA[8] = {1,1,1,1,0,0,0,0};
boolean DirB[8] = {1,1,0,0,0,0,1,1};

int n[8]={0,1,2,3,4,5,6,7};


void setup() {
  pinMode(motorPinDirA, OUTPUT);
  pinMode(motorPinDirB, OUTPUT);
  pinMode(motorPinPwmA, OUTPUT);
  pinMode(motorPinPwmB, OUTPUT);
  Serial.begin(9600);
}

void step(int dir){
  if (dir==1){
    nStep=(nStep+1)%8;
    digitalWrite(motorPinDirA, DirA[nStep]);
    digitalWrite(motorPinDirB, DirB[nStep]);
    digitalWrite(motorPinPwmA, PwmA[nStep]);
    digitalWrite(motorPinPwmB, PwmB[nStep]);
  }else{
    nStep=(nStep+1)%8;
    digitalWrite(motorPinDirA, DirA[7-nStep]);
    digitalWrite(motorPinDirB, DirB[7-nStep]);
    digitalWrite(motorPinPwmA, PwmA[7-nStep]);
    digitalWrite(motorPinPwmB, PwmB[7-nStep]);
  }
  
  //delay(delayTime);

}
 
void loop() {

vel=digitalRead(4);
step(vel);
delay(delayTime);

}
