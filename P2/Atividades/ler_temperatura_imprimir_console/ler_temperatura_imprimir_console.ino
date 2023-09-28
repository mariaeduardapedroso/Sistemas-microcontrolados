/*INCLUSÃO DAS BIBLIOTECAS*/
#include <OneWire.h>
#include <DallasTemperature.h>
//criar biblioteca
#include "exibe_disp.h"
#define a 22
#define b 23
#define c 24
#define d 25
#define e 26
#define f 27
#define g 28
#define port_unidade 2
#define port_dezena 3

const int sensorPin = 8; // Pino onde o sensor LM35 está conectado
float temperaturaC;      // Variável para armazenar a temperatura em graus Celsius
float voltage;           // Variável para armazenar a leitura do ADC

OneWire oneWire(sensorPin);
DallasTemperature sensors(&oneWire);

int unidade, dezena;
int cont = 0;
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
  Serial.begin(9600);  // Inicia a comunicação serial a 9600bps

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {
  Serial.print("\nRequerimento de temperatrura");
  sensors.requestTemperatures();

  Serial.print("\nValor da temperatrura: ");
  cont = sensors.getTempCByIndex(0);
  Serial.print(cont);

  dezena = cont / 10;
  unidade = cont % 10;

  exibe_disp(dezena, unidade);


  delay(1000); // Espera 1 segundo antes da próxima leitura
}
