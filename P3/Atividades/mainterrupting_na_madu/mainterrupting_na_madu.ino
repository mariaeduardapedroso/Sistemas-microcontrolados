#define ledPin 13

void setup(){
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  // Configuração do timer1

  TCCR1A = 0;
  //confira timer para operação
  //normal pinos OC1A e OC1B desconectados

  TCCR1B = 0;
  //limpa registrador
  // configura prescaler para 1: CS10 = 1

  TCCR1B |= (1 << CS10);

  TCNT1 = 0xC180;

  // incia timer com valor para que estouro ocorra em 1 MILIssegundo
  // 65536-(16MHz/1/1000Hz) = 49536 = 0xC180
  //FFFF - (veloicidade do clock/prescaler/segundo

  TIMSK1 |= (1 << TOIE1); // habilita a interrupção do TIMER1

}

int count;

void loop(){

  if (count == 999){

    count = 0;

    Serial.println(millis());
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);

    //inverte estado do led
    //a manipulação do led é feita na ISR

  }

}

ISR(TIMER1_OVF_vect) //interrupção do TIMER1
{

  TCNT1 = 0xC180;
  // Renicia TIMER

  count++;

}
