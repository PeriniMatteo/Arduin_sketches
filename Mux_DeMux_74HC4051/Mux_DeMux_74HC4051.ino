//This sketch aim to work with 74HC4051 Multiplexer / Demultiplexer
     
    int r0 = 0;      //value of select pin at the 4051 (s0)
    int r1 = 0;      //value of select pin at the 4051 (s1)
    int r2 = 0;      //value of select pin at the 4051 (s2)
    int count = 0;   //which y pin we are selecting
     
    void setup(){
     Serial.begin(9600);
      pinMode(7, OUTPUT);    // s0
      pinMode(6, OUTPUT);    // s1
      pinMode(5, OUTPUT);    // s2
      pinMode(A5, INPUT);
    }
     
    void loop () {
     
      for (count=0; count<=7; count++) {
     
        // select the bit  
        r0 = bitRead(count,0);    // use this with arduino 0013 (and newer versions)    
        r1 = bitRead(count,1);    // use this with arduino 0013 (and newer versions)    
        r2 = bitRead(count,2);    // use this with arduino 0013 (and newer versions)    
     
        //r0 = count & 0x01;      // old version of setting the bits
        //r1 = (count>>1) & 0x01;      // old version of setting the bits
        //r2 = (count>>2) & 0x01;      // old version of setting the bits
     
        digitalWrite(7, r0);
        digitalWrite(6, r1);
        digitalWrite(5, r2);
     
        //Either read or write the multiplexed pin here
        int sensorValue = analogRead(A5);
        Serial.print(count);
        Serial.print(" -> ");
        Serial.println(sensorValue);
        delay(200);
     
      }  
    }

