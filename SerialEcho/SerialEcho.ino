
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
}

void loop() { 
  // run over and over
  if (Serial.available()) {
    Serial.write(Serial.read());
  }
  //delay(random(1000));
}
