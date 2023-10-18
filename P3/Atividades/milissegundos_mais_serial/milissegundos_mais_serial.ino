void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com taxa de 9600 bps
}

void loop() {
  unsigned long currentMillis = millis(); // Obtém o tempo atual em milissegundos
  unsigned long seconds = currentMillis / 1000; // Converte milissegundos para segundos
  unsigned long minutes = seconds / 60; // Converte segundos para minutos
  seconds = seconds % 60; // Calcula os segundos restantes após remover os minutos

  // Transmite minutos e segundos pela porta serial
  Serial.print("Minutos: ");
  Serial.print(minutes);
  Serial.print(" - Segundos: ");
  Serial.println(seconds);

  delay(1000); // Aguarda 1 segundo antes de atualizar os valores na porta serial
}
