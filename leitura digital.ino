//EXEMPLO PRA 3 VARIAVEIS NO GRAFICO

int ledPin = 13;
int inPin = 7;
int val = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inPin, INPUT_PULLUP);
}

void loop() {

  if (!digitalRead(inPin)) {
    delay(50);
    if (digitalRead(inPin)) {
      val = !val;
    }
  }
  digitalWrite(ledPin, val);
}
