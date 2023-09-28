const byte ledPin = 12;
const byte interruptPin = 18;
volatile byte state = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  //quando estado muda
  //attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  //iterrupção por borda de subida
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
}
