#include <math.h> 
#define PI 3.1415926536

const int pinx= A2;
const int piny= A0;
const int pinz= A1;

double lecturas[3];
double analog[3];
double angulos[3];
int i=0;

double ax0= 506.75;
double ay0= 487.5;
double az0= 472.25;

double ax1= 10.72;
double ay1= 10.61;
double az1= 10.51;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  analog[0] = analogRead(pinx);
  analog[1] = analogRead(piny);
  analog[2] = analogRead(pinz);

  lecturas[0]=(analogRead(pinx)-ax0)*(ax1/1024.0);
  lecturas[1]=(analogRead(piny)-ay0)*(ay1/1024.0);
  lecturas[2]=(analogRead(pinz)-az0)*(az1/1024.0);


  angulos[0] = atan2( lecturas[0], sqrt(sq(lecturas[1])+sq(lecturas[2])))*180/PI;
  angulos[1] = atan2(lecturas[1], sqrt(sq(lecturas[0])+sq(lecturas[2])))*180/PI;
  angulos[2] = atan2(sqrt(sq(lecturas[0])+sq(lecturas[1])) , lecturas[2])*180/PI;

  //Serial.println();
  //Serial.print("Valoranalog x - Valor analog y - Valor analog z");
  //Serial.println();
  //for(i=0;i<3;i++){
  //  Serial.print(analog[i]);
  //  Serial.print("    -    ");
  //  Serial.println();
  //}

  Serial.println();
  Serial.print("Aceleracion x - Aceleracion y - Aceleracion z");
  Serial.println();
  for(i=0;i<3;i++){
    Serial.print(lecturas[i]);
    Serial.print("     -    ");
  }

  Serial.println();
  Serial.print("Angulo theta - Angulo psi - Angulo phi");
  Serial.println();
  for(i=0;i<3;i++){
    Serial.print(angulos[i]);
    Serial.print("     -    ");
  }

  //
  // Serial.print(lecturas[2]);
  // Serial.println();
  delay (200);
}
