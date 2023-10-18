unsigned long time;
bool aceso = true;
int pinLed = 13;
const long intervalo = 300; // intervaloo de tempo para ligar/desligar o LED (em milissegundos)
unsigned long ultimoTempo = 0; // Armazena o último tempo em que o LED foi alterado

void setup() {

  Serial.begin(9600);
  pinMode(pinLed, OUTPUT); // Configura o pino do LED como saída

}

void loop() {
  unsigned long tempoAtual = millis(); // Obtém o tempo atual

  Serial.print("Time: ");
  Serial.println(tempoAtual); // Imprime o tempo desde que o programa iniciou

  if (tempoAtual - ultimoTempo >= intervalo) {
    // Se passou tempo suficiente, liga/desliga o LED
    ultimoTempo = tempoAtual; // Salva o tempo atual

    if (digitalRead(pinLed) == HIGH) {
      digitalWrite(pinLed, LOW); // Desliga o LED
    } else {
      digitalWrite(pinLed, HIGH); // Liga o LED
    }
  }
}
