#define a 22
#define b 23
#define c 24
#define d 25
#define e 26
#define f 27
#define g 28
#define port_unidade 2
#define port_dezena 3

//criar biblioteca
#include "exibe_disp.h"

//int analogPin = A3;
//analog pin 3;

int val = 0;
int cont = 0;
int tempo = 0;
int unidade, dezena;

int display[10][7] = {
  //a, b, c, d, e, f, g
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};
void setup() {
  Serial.begin(9600);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(port_unidade, OUTPUT);
  pinMode(port_dezena, OUTPUT);
}

void loop() {
//  val = analogRead(analogPin);
//  Serial.println(val);
  //definir escala de 0 a 99
//  map(val, 0, 1023, 0, 99);

  tempo++;
  if (tempo == 100) {
    cont ++;
    tempo = 0;
  }


  if (cont > 99) {
    cont = 0;
  }
  
  dezena = cont / 10;
  unidade = cont % 10;

  exibe_disp(dezena, unidade);




}
