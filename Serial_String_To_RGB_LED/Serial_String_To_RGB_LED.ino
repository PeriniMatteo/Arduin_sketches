String inString = "";
void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);}
void loop() {
  if (Serial.available() > 0) {
    char inChar = Serial.read();
    if (inChar == '!') { 
      if (String(inString) == "verde"){
        digitalWrite(9,HIGH);
      }else{
        digitalWrite(9,LOW);}
      if (String(inString) == "blu"){
        digitalWrite(10,HIGH);
      }else{
       digitalWrite(10,LOW);}
      if (String(inString) == "rosso"){
        digitalWrite(11,HIGH);
      }else{
      digitalWrite(11,LOW);}
    Serial.println(inString);
    inString = ""; }
  else{inString+=inChar;}}}










