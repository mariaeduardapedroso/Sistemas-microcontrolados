unsigned long ultimoTempo = 0; // Armazena o último tempo em que o LED foi alterado

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com taxa de 9600 bps
}

void loop() {
  unsigned long tempoAtual = millis(); // Obtém o tempo atual em milissegundos
  const long intervalo = 1000;      // intervaloo para enviar a informação (1 segundo)
  unsigned long seconds = tempoAtual / 1000; // Converte milissegundos para segundos
  unsigned long minutes = seconds / 60; // Converte segundos para minutos
  seconds = seconds % 60; // Calcula os segundos restantes após remover os minutos


  if (tempoAtual - ultimoTempo >= intervalo) { // Verifica se já passou 1 segundo desde a última atualização
    
    ultimoTempo = tempoAtual;
    // Transmite minutos e segundos pela porta serial
    Serial.print("Minutos: ");
    Serial.print(minutes);
    Serial.print(" - Segundos: ");
    Serial.println(seconds);

    //delay(1000); // Aguarda 1 segundo antes de atualizar os valores na porta serial
  }
}
