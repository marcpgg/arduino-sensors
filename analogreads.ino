const int pinx= A2;
const int piny= A0;
const int pinz= A1;
double analog[3];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);



}

void loop() {
  
  analog[0] = analogRead(pinx);
  analog[1] = analogRead(piny);
  analog[2] = analogRead(pinz);

  Serial.println();
  Serial.print("Valor analog x - Valor analog y - Valor analog z");
  Serial.println();
  for(int i=0;i<3;i++){
    Serial.print(analog[i]);
    Serial.print("    -    ");
    Serial.println();
  }

}
