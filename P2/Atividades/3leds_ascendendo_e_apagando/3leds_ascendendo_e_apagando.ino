const int ledPin1 = 11;
const int ledPin2 = 12;
const int ledPin3 = 13;

unsigned long milissegAnterior = 0;
const int intervalo1 = 0; // Começo da animação do LED1
const int intervalo2 = 200; // Começo da animação do LED2
const int intervalo3 = 400; // Começo da animação do LED3

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT); 

}

void loop() {
  unsigned long milissegAtual = millis();

  // LED 1
  // Se o tempo atual está entre o início da animação do LED1 e 300ms depois
  if (milissegAtual - milissegAnterior >= intervalo1 && milissegAtual - milissegAnterior <= intervalo1 + 300) {
    // Mapeia o tempo dentro desse intervalo para um valor de brilho entre 0 e 255 (ascendendo)
    int brilho = map(milissegAtual - milissegAnterior - intervalo1, 0, 300, 0, 255);
    // Define o brilho do LED1 usando PWM
    analogWrite(ledPin1, brilho);
  } 
  // Se o tempo atual está entre 300ms e 600ms depois do início da animação do LED1
  else if (milissegAtual - milissegAnterior > intervalo1 + 300 && milissegAtual - milissegAnterior <= intervalo1 + 600) {
    // Mapeia o tempo dentro desse intervalo para um valor de brilho entre 255 e 0 (descendendo)
    int brilho = map(milissegAtual - milissegAnterior - intervalo1 - 300, 0, 300, 255, 0);
    // Define o brilho do LED1 usando PWM
    analogWrite(ledPin1, brilho);
  }

  // LED 2
  // Se o tempo atual está entre o início da animação do LED2 e 300ms depois
  if (milissegAtual - milissegAnterior >= intervalo2 && milissegAtual - milissegAnterior <= intervalo2 + 300) {
    // Mapeia o tempo dentro desse intervalo para um valor de brilho entre 0 e 255 (ascendendo)
    int brilho = map(milissegAtual - milissegAnterior - intervalo2, 0, 300, 0, 255);
    // Define o brilho do LED2 usando PWM
    analogWrite(ledPin2, brilho);
  }
  // Se o tempo atual está entre 300ms e 600ms depois do início da animação do LED2
  else if (milissegAtual - milissegAnterior > intervalo2 + 300 && milissegAtual - milissegAnterior <= intervalo2 + 600) {
    // Mapeia o tempo dentro desse intervalo para um valor de brilho entre 255 e 0 (descendendo)
    int brilho = map(milissegAtual - milissegAnterior - intervalo2 - 300, 0, 300, 255, 0);
    // Define o brilho do LED2 usando PWM
    analogWrite(ledPin2, brilho);
  }

  // LED 3
  // Se o tempo atual está entre o início da animação do LED3 e 300ms depois
  if (milissegAtual - milissegAnterior >= intervalo3 && milissegAtual - milissegAnterior <= intervalo3 + 300) {
    // Mapeia o tempo dentro desse intervalo para um valor de brilho entre 0 e 255 (ascendendo)
    int brilho = map(milissegAtual - milissegAnterior - intervalo3, 0, 300, 0, 255);
    // Define o brilho do LED3 usando PWM
    analogWrite(ledPin3, brilho);
  }
  // Se o tempo atual está entre 300ms e 600ms depois do início da animação do LED3
  else if (milissegAtual - milissegAnterior > intervalo3 + 300 && milissegAtual - milissegAnterior <= intervalo3 + 600) {
    // Mapeia o tempo dentro desse intervalo para um valor de brilho entre 255 e 0 (descendendo)
    int brilho = map(milissegAtual - milissegAnterior - intervalo3 - 300, 0, 300, 255, 0);
    // Define o brilho do LED3 usando PWM
    analogWrite(ledPin3, brilho);
  }

  // Resetar após completar a sequência de animação dos 3 LEDs
  if (milissegAtual - milissegAnterior >= intervalo3 + 600) {
    // Define o milissegAnterior como milissegAtual para reiniciar a animação desde o início
    milissegAnterior = milissegAtual;
  }
}
