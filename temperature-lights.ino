// Analog and digital pins used
const int red = 9;
const int green = 10;
const int blue = 11;
const int pinT= A3 ;

const double Tamb = 24.2;
const double Tmax = 28.2;
const int Namb = 508;
const int Nmax = 853;

// Common annode LEDs turn on with values of intensity between 255 (lowest) to 0 (highest. ie. 255-49 = 206
const int Rcolor[6] = {206, 0, 255,255,0,0};
const int Gcolor[6] = {255,255,0,0,0,255 };
const int Bcolor[6] =  {0,30, 60, 218, 255,255};
double lecturas_temp[7];
double tempRead;
double mtemp;
int N_temp;
float temp;
unsigned long tiempo=0;
double Vcc=5.0;

int i=0;

void setup() {
Serial.begin(9600);
pinMode(red, OUTPUT);
pinMode(green, OUTPUT);
pinMode(blue, OUTPUT);
}

void loop() {

	// test_leds()
	temp = lectura_temp();
	temp_led_plus(temp);

}

float lectura_temp(){
  
  //Lectura del LM35 para medir TEMPERATURA
	mtemp = (double)(Tmax-Tamb)/(double)(Nmax-Namb);
	N_temp = analogRead(pinT);
	temp=Tamb + mtemp * (N_temp - Namb);
	tempRead = temp;

	Serial.print("Dato temperatura=");
	Serial.println(N_temp);
	Serial.println();
    Serial.print("Temperatura");
    Serial.println();
    Serial.println(tempRead);

	delay(500);
  
  	return Temp;
  }

void temp_led_plus(float temp){

  // Common annode LEDs turn on with values of intensity between 255 (lowest) to 0 (highest. ie. 255-49 = 206
  // Example Spectrum  of 6 RGB colors.
  const int Rcolor[6] = {206, 0, 255,255,0,0};
  const int Gcolor[6] = {255,255,0,0,0,255 };
  const int Bcolor[6] =  {0,30, 60, 218, 255,255};
  int  colorTemp = map(temp,23,28,0,5);

  // Serial.println(colorTemp);
  analogWrite(red, Rcolor[colorTemp]);
  analogWrite(green, Gcolor[colorTemp]);
  analogWrite(blue, Bcolor[colorTemp]);
}

void temp_led_standard(){
	if (Temp > Tmax-0.5){
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    }
    else if (Temp < Tamb+0.5){
     digitalWrite(red, HIGH);
     digitalWrite(green, HIGH);
     digitalWrite(blue, LOW);
  	}
  	else{
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      digitalWrite(blue, HIGH);
  	}
  
}


void lectura_analogtemp(){
  Serial.println(analogRead(pinT));
  
}

void test_leds()
{
  turn_on(red);
  delay(100);
  turn_on(blue);
  delay(100);
  turn_on(green);
  delay(100);
  
  turn_off(red);
  turn_off(blue);
  turn_off(green);
}

void blink(int led)
{
  digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
}

void turn_on(int led)
{
  digitalWrite(led, LOW);
}

void turn_off(int led)
{
  digitalWrite(led, HIGH);
}
