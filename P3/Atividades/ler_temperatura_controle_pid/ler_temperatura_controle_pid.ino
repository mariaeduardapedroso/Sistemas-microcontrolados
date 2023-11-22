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
#define port_aquecedor 7

const int sensorPin = 8; // Pino onde o sensor LM35 está conectado
float temperaturaC;      // Variável para armazenar a temperatura em graus Celsius
float voltage;           // Variável para armazenar a leitura do ADC

OneWire oneWire(sensorPin);
DallasTemperature sensors(&oneWire);

int unidade, dezena;
float cont = 0;
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

//float T, erro, Kp;
//float Ki, saida, saidaAnterior;
float Ki, Kp, Kd;
float T1, T2, T3, Pid;
void loop() {
  Ki = 2;
  Kp = 20;
  Kd = 3;

  sensors.requestTemperatures();//requerimento da temperatura

  Serial.print("\nValor-da-temperatrura:");
  cont = sensors.getTempCByIndex(0);
  if (cont > -10.0) {
    Serial.print(cont);
    Serial.print(",");

    dezena = cont / 10;
    unidade = int(cont) % 10;

    T1 = controleProporcional(cont, 40, Kp);
    //  analogWrite(port_aquecedor, T1);
    Serial.print("Saida-Proporcional:");
    Serial.print(T1);
    Serial.print(",");

    T2 = controleIntegral(cont, 40, Ki);
    //  analogWrite(port_aquecedor, T2);
    Serial.print("Saida-Integrador:");
    Serial.print(T2);
    Serial.print(",");

    T3 = controleDerivativo(cont, 40, Kd);
    //  analogWrite(port_aquecedor, T3);
    Serial.print("Saida-Derivador:");
    Serial.print(T3);
    Serial.print(",");

    Pid = T1 + T2 + T3;

    if (Pid > 255) {
      Pid = 255;
    } else if (Pid < 0) {
      Pid = 0;
    }

    Serial.print("Saida-PID:");
    Serial.println(Pid);

    analogWrite(port_aquecedor, Pid);
  }


}

float controleProporcional(float temperatura, float tempIdeal, float Kp) {
  float erro;

  erro = tempIdeal - temperatura;

  return erro * Kp;
}

float erroAntAntAnt, erroAntAnt, erroAnt;

float controleIntegral(float temperatura, float tempIdeal, float Ki) {
  float erro;

  erroAntAntAnt = erroAntAnt;
  erroAntAnt = erroAnt;
  erroAnt = erro;
  erro = tempIdeal - temperatura;

  return Ki * (erro + erroAnt + erroAntAnt + erroAntAntAnt);
}

float controleDerivativo(float temperatura, float tempIdeal, float Kd) {
  float erro;

  erro = tempIdeal - temperatura;
  return Kd * (erro - erroAnt);
}


//interrupção do TIMER1
ISR(TIMER1_OVF_vect) {
  TCNT1 = 0xC180;
  // Renicia TIMER
  exibe_disp(dezena, unidade);
}

//delay(1000); // Espera 1 segundo antes da próxima leitura
