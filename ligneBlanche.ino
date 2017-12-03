#include <NewPing.h>

int pin1Moteur2 = 12; 
int pin2Moteur2 = 8; 
int pinPMoteur2 = 11;
int pin1Moteur1 = 2; 
int pin2Moteur1 = 4;
int pinPMoteur1 = 5;
int TRIG_PIN = 10;
int ECHO_PIN = 9;
int DIST_MAX = 200;
int i = 90;
int distActuelle = 0;
int cm;

// Code pour les phares
int pinPhoto = A0;
int valeurPhoto;
int pinLed = 3;
int luminositeLed; 

// Suiveur de ligne
int pinLineG = 7;
int pinLineD = 6;

NewPing sonar(TRIG_PIN, ECHO_PIN, DIST_MAX); // créé l'objet sonar


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin1Moteur1,OUTPUT);
  pinMode(pin2Moteur1,OUTPUT);
  pinMode(pinPMoteur1,OUTPUT);
  pinMode(pin1Moteur2,OUTPUT);
  pinMode(pin2Moteur2,OUTPUT);
  pinMode(pinPMoteur2,OUTPUT);

  pinMode(pinLineG, INPUT);
  pinMode(pinLineD, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  allumePhare();

  int lineHereG = checkLineG();
  int lineHereD = checkLineD();

  if (lineHereG == 1 && lineHereD == 1) {
    avance();
  } else if (lineHereG == 1 && lineHereD == 0) {
    tourneGauche();
   } else if (lineHereG == 0 && lineHereD == 1) {
    tourneDroite();
  } else {
    recule();
  }

  delay(300);
}

void dirMoteur(int moteur,int sens,int pourcentage){

  const int MOTOR1 = 1;
  const int MOTOR2 = 2;
  const int DIR_FORWARD = 1;
  const int DIR_BACK = -1;
  
  int pin1,etat1,pin2,etat2,pinP,puissance; //variable de la fonction
  

  if (moteur == MOTOR1){
    pin1 = pin1Moteur1;
    pin2 = pin2Moteur1;
    pinP = pinPMoteur1;
  }
  else {
    pin1 = pin1Moteur2;
    pin2 = pin2Moteur2;
    pinP = pinPMoteur2;
  }
  if (sens == DIR_FORWARD){
    etat1 = 1;
    etat2 = 0;
  }
  else if (sens == DIR_BACK){
    etat1 = 0;
    etat2 = 1;
  }
  else {
    etat1 = 0;
    etat2 = 0;
  }
  puissance = map(pourcentage,0,100,0,255);
  analogWrite(pinP, puissance);
  digitalWrite(pin1, etat1);
  digitalWrite(pin2, etat2);
}

void avance(){
  dirMoteur(1,1,80); 
  dirMoteur(2,1,80); 
}

void recule(){ 
  dirMoteur(1,-1,80); 
  dirMoteur(2,-1,80); 
}

void tourneDroite(){ 
  dirMoteur(1, 1, 50 ); 
  dirMoteur(2, 1, 100); 
}

void tourneGauche() {
  dirMoteur(1, 1, 100);
  dirMoteur(2, 1, 50); 
}

int lectureDistance() { // Envoi la distance mesurée par le capteur de distance
  delay(70);

  unsigned int uS = sonar.ping(); // lance la function ‘ping’ de l’objet ‘sonar’
  cm = uS / US_ROUNDTRIP_CM; // converti la distance en
  if(cm == 0){
    lectureDistance();
  }
  else{
    Serial.println(cm);
    return cm;
  }
}

void allumePhare() {
  valeurPhoto = analogRead(pinPhoto);
  Serial.print("Analog reading = ");
  Serial.print(valeurPhoto);
  luminositeLed = max(map(valeurPhoto, 0, 400, 255, 0), 0);
  Serial.print(" Analog write = ");
  Serial.println(luminositeLed);
  analogWrite(pinLed, luminositeLed);
}

int checkLineG() {
  return digitalRead(pinLineG);
}

int checkLineD() {
  return digitalRead(pinLineD);
}

