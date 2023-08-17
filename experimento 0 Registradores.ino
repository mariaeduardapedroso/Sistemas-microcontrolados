//void setup() {
// //os 3 faz o mesmo trabalho de forma diferente
// //registrador conectado a porta 2
// DDRE = B11111110; // sets Arduino pins 1 to 7 as outputs, pin O | 1-7 saida e 0 entrada as input
// //Mascara logica ou se ta um vai pra um se ta zero é indiferente so valor não muda
// DDRE = DDRE | B11111100; // this is safer as it sets pins 2 to 7 as outputs
// // without changing the value of pins 0 & 1, which are RX & TX
// //mascara com notação do c
// DDRE |= B11111100;
//}


//void loop() {
// PORTE |= B00000100; // Pin D2 to HIGH
// delay(100);
// mascara com and SERÁ O CONTRÁRIO - altera estado só do bit zero
// PORTE &= B11111011; // Pin D2 to LOW
// delay(100);
//}



//LED INTEGRADO (B7) MAIS LED NA PORTA 2 (E2)
/*
void setup() {
  //mascara com notação do c
  //portas que estão pwm
  DDRE = B11111110;
  DDRE |= B11111100;
  //potas que esta o led interno
  DDRB = B10000000;
  DDRB |= B10000000;
}


void loop() {
  PORTE |= B00010000; // Pin D2 to HIGH
  PORTB |= B10000000;
  delay(1000);
  PORTE &= B11101111; // Pin D2 to LOW
  PORTB &= B01111111;
  delay(1000);
}
*/

//LED INTEGRADO (B7) MAIS LED NA PORTA 2 (E2)
void setup() {
  pinMode(2,OUTPUT); //PORTA 2
  pinMode(13,OUTPUT); //LED INTEGRADO
}


void loop() {
  digitalWrite(2,HIGH);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  digitalWrite(13,LOW);
  delay(1000);
}
