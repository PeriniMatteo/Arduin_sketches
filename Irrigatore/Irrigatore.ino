//this is the code of this project:
//https://github.com/musefablab/FEM-MUSina
//Follow the above link to more informations 

//*******************************************************************
//Matteo Perini
//
//2015 05 19     ver. 1.00
//2015 05 21     ver. 1.01 G.B. Toller 
//
//Software base per la gestione della macchina irrigua FEM MUSina
//
//2015 05 21: aggiunto array soglia[8] per diversificare interventi 
//*******************************************************************

//*******************************************************************
//operazioni preliminari
//*******************************************************************

//-------------------------------------------------------------------
//include librerie
//-------------------------------------------------------------------
#include <Servo.h> 

//-------------------------------------------------------------------
//dichiarazioni e definizioni di oggetti e variabili
//-------------------------------------------------------------------

Servo myservo;             //creo un oggetto di classe Servo

int motorPinDirA = 12;     //i pin da collegare al motore
int motorPinDirB = 13;
int motorPinPwmA = 3;
int motorPinPwmB = 11;

int delayTime = 20;        //tempo di ritardo 

int EVPin=4;               //il pin da collegare all'elettro-valvola 
int ServoPin=10;           //il pin da collegare al servo
int pinStop=2;

//variabili di servizio
int dir=1;                 //direzione del motore
int nStep=0;               //contatore numero di passi del motore
long int T0;               //millisecondi segnati dal timer

//variabili per la selezione dell'ingresso sul multiplexer
int r0 = 0;                //value of select pin at the 4051 (s0)
int r1 = 0;                //value of select pin at the 4051 (s1)
int r2 = 0;                //value of select pin at the 4051 (s2)

int count = 0;             //which y pin we are selecting

//dichiar. e iniz. a 1023 punti dell'array dove verranno
//immagazzinati i valori di resistenza, proxy dell'umidita' 
int humidity[8]={1023,1023,1023,1023,  1023,1023,1023,1023};

//dichiar. e iniz. dell'array con soglie di irrigazione di ogni vaso
int soglia[8]  ={800,800,800,800,  800,800,800,800};

int StepXpos=195;          //passi di motore tra due uscite

//dich. e iniz. degli array per l'avanzamento del motore
boolean PwmA[8] = {1,1,1,0,1,1,1,0};
boolean PwmB[8] = {1,0,1,1,1,0,1,1};
boolean DirA[8] = {1,1,1,1,0,0,0,0};
boolean DirB[8] = {1,1,0,0,0,0,1,1};

int TempoDiAnnaffiamento=25000;  //tempo apertura valvola [ms]


//*******************************************************************
//dichiarazioni e definizioni di funzioni
//*******************************************************************

//*******************************************************************
// FUNZIONE SETUP
// put your setup code here, to run once:
// the setup routine runs once when you press reset:
//*******************************************************************
void setup() {
  pinMode(motorPinDirA, OUTPUT);  // Direzione Canale A del motore
  pinMode(motorPinDirB, OUTPUT);  // Direzione Canale B del motore
  pinMode(motorPinPwmA, OUTPUT);  // Impulso A del motore
  pinMode(motorPinPwmB, OUTPUT);  // Impulso B del motore
  pinMode(7, OUTPUT);             // s0 Multiplexer
  pinMode(6, OUTPUT);             // s1 Multiplexer
  pinMode(5, OUTPUT);             // s2 Multiplexer
  pinMode(A5, INPUT);      // Lettura delle resistenze del terreno
  pinMode(EVPin, OUTPUT);  // Elettrovalvola
  pinMode(pinStop, INPUT);
  Serial.begin(9600);      // Inizializzo la Seriale
  T0=millis();             // Azzero T0 su millis(); inizio attesa
  myservo.attach(ServoPin);       // Inizializzo il servo sul pin 10
  myservo.write(0);               // Azzero la posizione del servo
}

//-------------------------------------------------------------------
//funzione di avanzamento o arretramento di un passo 
//-------------------------------------------------------------------
void step(int dir){
  if (dir==1){                                 //avanza
    nStep=(nStep+1)%8;
    digitalWrite(motorPinDirA, DirA[nStep]);
    digitalWrite(motorPinDirB, DirB[nStep]);
    digitalWrite(motorPinPwmA, PwmA[nStep]);
    digitalWrite(motorPinPwmB, PwmB[nStep]);
  }else{                                       //arretra
    nStep=(nStep+1)%8;
    digitalWrite(motorPinDirA, DirA[7-nStep]);
    digitalWrite(motorPinDirB, DirB[7-nStep]);
    digitalWrite(motorPinPwmA, PwmA[7-nStep]);
    digitalWrite(motorPinPwmB, PwmB[7-nStep]);
  }
}

//-------------------------------------------------------------------
//funzione di misura della tensione sul partitore resistivo (umidita') 
//degli 8 canali, espressa in punti del convertitore AD
//NOTA: legge la tensione generata dal partitore: resist. 10 kohm -
//  resistenza variabile del suolo. Suolo SECCO->resist.suolo ALTA->
//  ->tensione sul partitore ALTA
//-------------------------------------------------------------------
void check_humidity(){
  Serial.println("checking...");
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//INIZIO ciclo dei sensori di umidita'
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
        for (count=0; count<=7; count++) {   
        // select the bit  
        r0 = bitRead(count,0);    // Reads a bit of a number   
        r1 = bitRead(count,1);    //  
        r2 = bitRead(count,2);    //  
     
        digitalWrite(7, r0);      // Scrive il bit su digital Output
        digitalWrite(6, r1);      //
        digitalWrite(5, r2);      //
     
        //Either read or write the multiplexed pin here
        int sensorValue = analogRead(A5);
        humidity[count] = sensorValue;    //carica dati sull'array
        }
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
}  //FINE ciclo dei sensori di umidita'
  
 
//-------------------------------------------------------------------
//funzione che fa arretrare il motore fino al fine-corsa del revolver 
//NOTA: lo switch di fine corsa è connesso con l'ingresso digitale #2
//-------------------------------------------------------------------
void azzera_stepper(){
  analogWrite(motorPinPwmA, 255);
  analogWrite(motorPinPwmB, 255);
  Serial.println("I'm going...");
  while(!(digitalRead(pinStop)==HIGH)){
   step(-1);
   ////delay(20);
   delay(2);
  }
Serial.println("Home reached!");
  delay(2000);
}


//-------------------------------------------------------------------
//funzione che riceve in input l'indice (0...7) del vaso da irrigare
//1) posiziona il revolver sulla giusta linea
//2) abbassa il revolver tramite il servo
//3) aspetta
//4) apre la valvola
//5) aspetta per il tempo stabilito di irrigazione
//6) chiude la valvola
//7) aspetta
//8) alza il revolver tramite il servo
//-------------------------------------------------------------------
void annaffia(int Da_irrigare){
  Serial.println("Going to the right position...");
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//INIZIO ciclo per il posizionamento del revolver sulla linea
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo 
for (count=(Da_irrigare*StepXpos*2); count>=0; count--){
  Serial.println("Step");
  step(1);
  //delay(20);
  delay(2);
  
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo 
}  //FINE ciclo per il posizionamento del revolver

Serial.println("Position reached!");
//Serial.println("Going to the right position...");
Serial.println("Pull down...");
myservo.write(70);
delay(500);
Serial.println("Watering...");
digitalWrite(EVPin, HIGH);
Serial.println("Please wait...");
delay(TempoDiAnnaffiamento);
Serial.println("Turn off the valve...");
digitalWrite(EVPin, LOW);
Serial.println("Please wait a little...");
delay(2000);
Serial.println("Pulll up...");
myservo.write(0);
}
 
 
//*******************************************************************
//FUNZIONE LOOP che viene eseguita come loop infinito
//*******************************************************************
void loop() {
  analogWrite(motorPinPwmA, 0);
  analogWrite(motorPinPwmB, 0);
if ((millis()-T0)>5000){    //si lavora se il tempo attuale millis() 
                            //meno l'ultimo T0 e' >3000
  T0=millis();
  Serial.println("check humidity...");   
  check_humidity();         //misura della tensione al partitore
                            //resistivo, ~ recipr.umidita'
  //if 
//vel=digitalRead(4);
//step(vel);
for (count=0; count<=6; count++) {
  Serial.print(humidity[count]);  //stampo le resistenze misurate
  Serial.print(" , ");
}
  Serial.println(humidity[7]);
  Serial.println("");
  //delay(delayTime);
  Serial.println("Controlling values...");


//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//INIZIO ciclo delle linee irrigue. Ciclo delle linee (0...7)
//con resist. oltre la soglia di x punti (test=800), si irriga
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
for (count=0; count<=7; count++) {
/////  if (humidity[count]<800){         //versione semplificata v.1.00
  if (humidity[count]<soglia[count]){
    Serial.print("Humidity at the ");
    Serial.print(count+1);
    Serial.println("th vase voltage is too low!");
    Serial.println("Try to water the plant");
    Serial.println("Go to home position...");
    azzera_stepper();
    int Da_irrigare=count+1;
    Serial.println("Water the plant");
    annaffia(Da_irrigare);
    Serial.println("Plant watered!");
    break;
  }else{
    Serial.print("Plant ");
    Serial.print(count+1);
    Serial.println(" doesn't need water...");
    }
//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
}  //FINE ciclo delle linee irrigue

//stampe di controllo
Serial.println("Waiting for new check humidity...");
Serial.println("");

}
//Serial.print(digitalRead(2));
}
