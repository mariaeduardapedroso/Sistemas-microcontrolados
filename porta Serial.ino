//COLOCANDO PORTAS SERIAIS, POREM SÓ A PRIMEIRA UTILIZAMOPS O RESTO SE COMUNICA PELO COMUNICATION TX1...

void setup() {
  Serial.begin(9600); //Comunicação serial normal do areduino com pc
//Serial1.begin(9600); tx1
//Serial2.begin(9600); tx2

}

void loop() {
  Serial.println("EU SOU A MADU");
//Serial1.println("EU SOU A MADU 1"); tx1
//Serial2.println("EU SOU A MADU 2"); tx2

}
