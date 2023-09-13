// Definindo o pino do LED
const int ledPin = 13;

void setup() {
  // Configurando o pino do LED como saída
  pinMode(ledPin, OUTPUT);
}
//100 - 0 em 300ms
//0 - 100 em 300ms

void loop() {

  for (int i = 0; i <= 30; i++) {
    // Liga o LED
    digitalWrite(ledPin, HIGH);
    delay(i / 3);

    // Desliga o LED
    digitalWrite(ledPin, LOW);
    delay(10 - i / 3);
  }

  for (int i = 0; i <= 30; i++) {

    // Desliga o LED
    digitalWrite(ledPin, LOW);
    delay(i / 3);

    // Liga o LED
    digitalWrite(ledPin, HIGH);
    delay(10 - i / 3);
  }

}
