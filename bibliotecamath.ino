//EXEMPLO PRA USAT BIBLIOTECA MATH

float contador = 0;
#include "math.h";

void setup() {
  Serial.begin(9600); //Comunicação serial normal do areduino com pc
}

void loop() {
  contador++;
  delay(500);
  //PARA PLOTER SERIAL

  Serial.println(sin(contador/10));
}
