
int incomingByte = 0; //para dados recebidos na porta serial

void setup() {
  Serial.begin(9600);

}

void loop() {
  //enviar resposta apenas quando receber dados
  if (Serial.available() > 0) {
    //le o dado recebido
    incomingByte = Serial.read();
    //responder o que foi recebido ele pega caracter por caracter em tabela ascii
    Serial.print("Eu recebi em acii:");
    Serial.println(incomingByte, DEC);

        Serial.print("Eu recebi:");
    Serial.println((char)incomingByte);
  }

}
