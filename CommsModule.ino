#include <SFE_BMP180.h>
#include <Wire.h>
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
#include <math.h>
#define PI 3.1415926536

// Pines digitales
const int trig = 2;
const int echo = 3;
const int tx = 12;
const int rx = 13;
// pines analogicos
const int da= A4;
const int cl= A5;

double lecturas[3];
double angulos[3];
double Vcc = 5.0;

SFE_BMP180 bmp;
SoftwareSerial BT(tx, rx);   // Definimos los pines RX y TX del Arduino conectados al Bluetooth

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  bmp.begin();
}

void loop() {
  double temp, presion;
  
  lecturas[0] = getDistancia();
  getTempPresion(temp, presion);
  lecturas[1] = presion;
  lecturas[2] = temp;
  getInclinacion();

  // Mostrar datos por Terminal BT o bien por monitor 
  // si no se encuentra disponible
  while (BT.available() || Serial.available()) {
    if (BT.read() == '1') {
      bluetooth();
    }
    if (Serial.read() == '1') {
      serie();
    }
  }
}

void bluetooth() {
  BT.println();
  BT.println("Dist - Pres - Temp");
  BT.print(lecturas[0]);
  BT.print(" - ");
  BT.print(lecturas[1]);
  BT.print(" - ");
  BT.println(lecturas[2]);
  BT.println();
  BT.println("Inclinaciones:");
  BT.print("theta  -  psi -  phi");
  BT.println();
  for (int i = 0; i< 2; i++){  
    BT.print(angulos[i]);
    BT.print(" - ");
  }
  BT.println(angulos[2]);
  BT.println();
  
}

void serie() {

  int i = 0;
  Serial.println();
  Serial.print("Dist  -  Pres  - Temp");
  Serial.println();
  for (i = 0; i < 2; i++) {
    Serial.print(lecturas[i]);
    Serial.print(" - ");
  }
  Serial.println(lecturas[2]);
  Serial.println();
  Serial.print("Inclinacion:");
  Serial.println();
  Serial.print("theta  -  psi -  phi");
  Serial.println();
  for (i = 0; i< 2; i++){  
    Serial.print(angulos[i]);
    Serial.print(" - ");
  }
  Serial.println(angulos[2]);
  Serial.println();
  Serial.println();
}

double getDistancia() {
  //Lectura del sensor de ultrasonidos para medir DISTANCIA
  unsigned long tiempo = 0;
  double distancia = 0;

  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  tiempo = pulseIn(echo, HIGH);
  distancia = tiempo / 58;
  if (distancia < 200 && distancia > 2) {
    return distancia;
  } else {
    return -1;
  }
}


void getTempPresion(double &Temp, double &Pres) {
    // Variables Temp y Pres pasadas por referencia para mayor claridad en el void loop .
    
  //Lectura del sensor barométrico BMP-180 para medir PRESION y TEMPERATURA
  char status;
  status = bmp.startTemperature();
  if (status != 0) {
    delay(status);
    status = bmp.getTemperature(Temp);
    if (status != 0) {
      status = bmp.startPressure(3);
      if (status != 0) {
        delay(status);
        status = bmp.getPressure(Pres, Temp);
        if (status == 0 ) {
          Pres = -1;
          Temp = -1;
        }
      }
    }
  }
}

void getInclinacion(){
  
  const int pinx= A2;
  const int piny= A0;
  const int pinz= A1;
  double ax0= 506.75;
  double ay0= 487.5;
  double az0= 472.25;
  double ax1= 10.72;
  double ay1= 10.61;
  double az1= 10.51;
  double accel[3];
  
  accel[0]=(analogRead(pinx)-ax0)*(ax1/1024.0);
  accel[1]=(analogRead(piny)-ay0)*(ay1/1024.0);
  accel[2]=(analogRead(pinz)-az0)*(az1/1024.0);

  angulos[0] = atan2( lecturas[0], sqrt(sq(lecturas[1])+sq(lecturas[2])))*180/PI;
  angulos[1] = atan2(lecturas[1], sqrt(sq(lecturas[0])+sq(lecturas[2])))*180/PI;
  angulos[2] = atan2(sqrt(sq(lecturas[0])+sq(lecturas[1])) , lecturas[2])*180/PI;

}
