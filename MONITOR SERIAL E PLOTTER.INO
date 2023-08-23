//EXEMPLO PRA USAR MONITOR SERIAL E O PLOTTER

int contador = 0;

void setup() {
  Serial.begin(9600); //Comunicação serial normal do areduino com pc
}

void loop() {
  //PARA MONITOR SERIAL
  //Serial.println("ACRESCENTA");
  //Serial.print("VALOR DA VARIAVEL: ");
  contador++;
  delay(500);
  //PARA PLOTER SERIAL
  Serial.println(contador);
}
