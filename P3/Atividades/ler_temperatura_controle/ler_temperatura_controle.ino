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
#define port_aquecedor 46

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
  Serial.begin(115200);  // Inicia a comunicação serial a 9600bps

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(port_unidade, OUTPUT);
  pinMode(port_dezena, OUTPUT);
  pinMode(port_aquecedor, OUTPUT);

  //interrupção
  // Configuração do timer1
  TCCR1A = 0;
  //confira timer para operação
  //normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;
  //limpa registrador
  // configura prescaler para 1: CS10 = 1
  TCCR1B |= (1 << CS10);
  TCNT1 = 0xC180;
  // incia timer com valor para que estouro ocorra em 1 segundo
  // 65536-(16MHz/1/1000Hz) = 49536 = 0xC180
  TIMSK1 |= (1 << TOIE1); // habilita a interrupção do TIMER1

}

void loop() {
  Serial.print("\nRequerimento de temperatrura");
  sensors.requestTemperatures();

  Serial.print("\nValor da temperatrura: ");
  cont = sensors.getTempCByIndex(0);
  Serial.print(cont);

  dezena = cont / 10;
  unidade = cont % 10;

  if (cont <= 40) {
    digitalWrite(port_aquecedor, HIGH);
    Serial.print("\n\nAQUECENDO");
  } else {
    digitalWrite(port_aquecedor, LOW);
  }

}

//interrupção do TIMER1
ISR(TIMER1_OVF_vect) {
  TCNT1 = 0xC180;
  // Renicia TIMER
  exibe_disp(dezena, unidade);
}

//delay(1000); // Espera 1 segundo antes da próxima leitura
