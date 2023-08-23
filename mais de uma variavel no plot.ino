//EXEMPLO PRA 3 VARIAVEIS NO GRAFICO

int contador = 0;
int contador1 = 0;
int contador2 = 0;
#include "math.h";

void setup() {
  Serial.begin(9600); //Comunicação serial normal do areduino com pc
}

void loop() {
  contador++;
  contador1--;
  contador2=contador2+2;
  delay(500);
  //PARA PLOTER SERIAL

  //para colocar mais de uma variavel tem que por espaço
  Serial.print("contador:");
  Serial.print(contador);
  Serial.print(" contador1:");
  Serial.print(contador1);
  Serial.print(" contador2:");
  Serial.print(contador2);
  Serial.print(" Seno:");
  Serial.println(sin(contador));
  
}
