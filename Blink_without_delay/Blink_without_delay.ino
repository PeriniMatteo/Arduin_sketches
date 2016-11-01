
int led = 13;
int long t;
boolean state;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  state=LOW;
t=millis();
}

// the loop routine runs over and over again forever:
void loop() {
  if((millis()-t)>=3000){ //3000 is the delay time
    if(state==LOW){
      digitalWrite(led, HIGH);
      state=HIGH;
    }
    else
    {
      digitalWrite(led, LOW);
      state=LOW;
    }
   t=millis(); 
}
}
