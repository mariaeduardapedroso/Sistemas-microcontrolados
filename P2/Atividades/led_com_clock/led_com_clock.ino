// Definindo o pino do LED
const int ledPin = 13;

void setup() {
  // Configurando o pino do LED como saída
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Liga o LED
  digitalWrite(ledPin, HIGH);
  // Espera 300ms
  delay(300);
  
  // Desliga o LED
  digitalWrite(ledPin, LOW);
  // Espera 300ms
  delay(300);
}
