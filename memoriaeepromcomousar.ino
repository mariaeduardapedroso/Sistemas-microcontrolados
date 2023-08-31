#include <EEPROM.h>

int addr = 0;
char ch;

void setup() {
  Serial.begin(9600);
  ch = EEPROM.read(addr);
}

void loop() {
  //enviar resposta apenas quando receber dados
  if (Serial.available() > 0) {
    //le o dado recebido
    ch = Serial.read();
    //gravar na eeprom
    EEPROM.write(addr, ch);
    Serial.println(ch);
  }
  Serial.print("Eu recebi:");
  Serial.println(ch);
  delay(1000);


}
