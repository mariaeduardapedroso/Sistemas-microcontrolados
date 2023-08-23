//COLOCANDO LED L INTERNO PRA PISCAR
int pinLed = 13;

void setup() {
  Serial.begin(9600); //Comunicação serial normal do areduino com pc
  pinMode(pinLed,OUTPUT);
}

void loop() {
  Serial.println("LIGA");
  digitalWrite(pinLed,HIGH);
  delay(100);
  Serial.println("DESLIGA");
  digitalWrite(pinLed,LOW);
  delay(100);
}
