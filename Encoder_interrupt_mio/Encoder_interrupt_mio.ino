int encoderPin1 = 2;
int encoderPin2 = 3;
long int count     = 0;
 
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
 
long lastencoderValue = 0;
 
int lastMSB = 0;
int lastLSB = 0;
 
void setup() {
  Serial.begin (9600);
 
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
 
  digitalWrite(encoderPin1, INPUT_PULLUP); //turn pullup resistor on
  digitalWrite(encoderPin2, INPUT_PULLUP); //turn pullup resistor on

 
  attachInterrupt(0, updateEncoder, CHANGE); //correspond to pin D2 in Arduino UNO
  attachInterrupt(1, updateEncoder, CHANGE); //correspond to pin D3 in Arduino UNO
 
}
 
void loop(){
  Serial.println(encoderValue);
}
 
void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
}
