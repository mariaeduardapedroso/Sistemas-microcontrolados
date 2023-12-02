#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

//rfid
#define RST_PIN         7          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

//magnetica tranca
const int SENSOR_PIN = 13;

const int DARK_THRESHOLD = 100; // you might need to adjust this based on testing

//servomotor
Servo myservo;
const int redled = 10;
const int greenled = 11;
const int buzz = 8;
int pos = 0; // LCD Connections

//lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte rows = 4;
const byte cols = 3;

////teclado
const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 4; //QUANTIDADE DE COLUNAS DO TECLADO

//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte PinosqtdLinhas[qtdLinhas] = {38, 39, 40, 41}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {42, 43, 44, 45}; //PINOS UTILIZADOS PELAS COLUNAS
//INICIALIZAÇÃO DO TECLADO
Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);

//aleatorio
int tamanhoSenha = 4;
char password[10] = "4567";
int currentposition = 0;
int invalidcount = 0;



void setup()
{
  displayscreen();
  Serial.begin(9600);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzz, OUTPUT);
  myservo.attach(9); //SERVO ATTACHED//

  pinMode(SENSOR_PIN, INPUT_PULLUP);

  lcd.begin(16, 2);

  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  inicialTune();
}

void inicialTune() {
  // Replace this with the notes and durations of your Christmas tune
  int melody[] = {NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5};
  int noteDurations[] = {8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 4};

  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(buzz, melody[i], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzz);
  }
}

void loop()
{
  char tecla_pressionada = meuteclado.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA

  if (tecla_pressionada) { //SE ALGUMA TECLA FOR PRESSIONADA, FAZ
    Serial.print("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println(tecla_pressionada); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
  }


  if ( currentposition == 0)
  {
    displayscreen();

  }

  int l ;

  char code = tecla_pressionada;
  if (code != NO_KEY)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SENHA:");
    lcd.setCursor(7, 1);
    lcd.print(" ");
    lcd.setCursor(7, 1);
    for (l = 0; l <= currentposition; ++l)
    {

      lcd.print("*");
      keypress();
    }

    if (code == password[currentposition])
    {
      ++currentposition;
      if (currentposition == tamanhoSenha)
      {

        unlockdoor();
        currentposition = 0;

      }
      Serial.println("INVALIDO CONTADOR OK");
      invalidcount = 0;

    }
    else
    {
      invalidcount = invalidcount + 1;
      Serial.println("INVALIDO CONTADOR BAD");
      Serial.println(invalidcount);
      incorrect();
      currentposition = 0;

    }
    if (invalidcount == 5)
    {

      ++invalidcount;
      torture1();

    }
    if (invalidcount >= 8)
    {
      torture2();
    }

  }





  int proximidade = digitalRead(SENSOR_PIN);
  if (proximidade == LOW) {
    Serial.println("FECHADO");
    inicialTune();
  }







  //RFID
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  // LOOP ENDS!!!//
}

//*********************Abrir a porta****************************//

void unlockdoor()
{
  delay(900);

  lcd.setCursor(0, 0);
  lcd.println(" ");
  lcd.setCursor(1, 0);
  lcd.print("Autorizado");
  lcd.setCursor(4, 1);
  lcd.print("BEM-VINDO");

  unlockbuzz();

  for (pos = 180; pos >= 0; pos -= 5) //   De 180 graus para 0 graus
  {
    myservo.write(pos); // servo para posição na variável 'pos'
    delay(5); // espera 15ms para servo atingir a posição
  }
  delay(2000);



  delay(1000);
  counterbeep();

  delay(1000);

  for (pos = 0; pos <= 180; pos += 5) // de 0 graus para 180 graus
  { // in steps of 1 degree
    myservo.write(pos); // servo para posição na variável 'pos'
    delay(15);


    currentposition = 0;

    lcd.clear();
    displayscreen();

  }
}

//*****************Código errado***********************//

void incorrect()
{
  delay(500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("CODIGO");
  lcd.setCursor(1, 1);
  lcd.print("INCORRETO");
  lcd.setCursor(15, 1);

  Serial.println("CÓDIGO INCORRETO. NÃO AUTORIZADO");
  digitalWrite(redled, HIGH);
  tone(buzz, NOTE_E1, 1000);  // Você pode ajustar a frequência e a duração do beep aqui
  delay(500);  // Adiciona um pequeno atraso para separar beeps consecutivos (ajuste conforme necessário)
  noTone(buzz);  // Para o beep
  delay(3000);
  lcd.clear();
  digitalWrite(redled, LOW);
  displayscreen();
}
//*************Limpar tela****************//
void clearscreen()
{
  lcd.setCursor(0, 0);
  lcd.println(" ");
  lcd.setCursor(0, 1);
  lcd.println(" ");
  lcd.setCursor(0, 2);
  lcd.println(" ");
  lcd.setCursor(0, 3);
  lcd.println(" ");
}
//******************************KEYPRESS***********************************//
void keypress()
{
  tone(buzz, NOTE_C6, 100);  // Você pode ajustar a frequência e a duração do beep aqui
  delay(50);  // Adiciona um pequeno atraso para separar beeps consecutivos (ajuste conforme necessário)
  noTone(buzz);  // Para o beep
}
//************************Display****************************//
void displayscreen()
{

  lcd.setCursor(0, 0);
  lcd.println("*DIGITE A SENHA*");
}
//*************************** ARM SERVO****************************************************************************//
void armservo()
{

  for (pos = 180; pos <= 180; pos += 50)
  {
    myservo.write(pos);
    delay(5);
  }
  delay(5000);

  for (pos = 180; pos >= 0; pos -= 50)
  {
    myservo.write(pos);
  }

}
//********************************UNLOCK BUZZ***********************************//
void unlockbuzz()
{

  for (int i = 0; i < 4; i++) {
    tone(buzz, NOTE_C6, 100);  // Você pode ajustar a frequência e a duração do beep aqui
    delay(500);
    noTone(buzz);
  }
}

//*******************************COUNTER BEEP*************************************//
void counterbeep()
{
  delay(1200);


  lcd.clear();
  digitalWrite(buzz, HIGH);

  lcd.setCursor(2, 15);
  lcd.println(" ");
  lcd.setCursor(2, 14);
  lcd.println(" ");
  lcd.setCursor(2, 0);
  delay(200);
  lcd.print("FECHANDO EM:::");

  lcd.setCursor(4, 1);
  lcd.print("5");
  delay(200);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("FECHANDO EM:");
  digitalWrite(buzz, LOW);
  delay(1000);
  //2
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2, 0);
  lcd.print("FECHANDO EM:");
  lcd.setCursor(4, 1); //2
  lcd.print("4");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("FECHANDO EM:");
  digitalWrite(buzz, LOW);
  delay(1000);
  //3
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2, 0);
  lcd.print("FECHANDO EM:::");
  lcd.setCursor(4, 1); //3
  lcd.print("3");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("FECHANDO EM:::");
  digitalWrite(buzz, LOW);
  delay(1000);
  //4
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2, 0);
  lcd.print("FECHANDO EM:::");
  lcd.setCursor(4, 1); //4
  lcd.print("2");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("FECHANDO EM:::");
  digitalWrite(buzz, LOW);
  delay(1000);
  //
  digitalWrite(buzz, HIGH);
  lcd.setCursor(4, 1);
  lcd.print("1");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN::");
  digitalWrite(buzz, LOW);
  delay(1000);
  //5
  digitalWrite(buzz, HIGH);
  delay(40);
  digitalWrite(buzz, LOW);
  delay(40);
  digitalWrite(buzz, HIGH);
  delay(40);
  digitalWrite(buzz, LOW);
  delay(40);
  digitalWrite(buzz, HIGH);
  delay(40);
  digitalWrite(buzz, LOW);
  delay(40);
  digitalWrite(buzz, HIGH);
  delay(40);
  digitalWrite(buzz, LOW);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("RE-LOCKING");
  delay(500);
  lcd.setCursor(12, 0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(13, 0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(14, 0);
  lcd.print(".");
  delay(400);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("FECHADO!");
  delay(440);
}
//*****************************TORTURE1****************************************//
void torture1()
{
  delay(1000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("AGUARDE POR ");
  lcd.setCursor(5, 1);
  lcd.print("15 SEGUNDOS.");
  digitalWrite(buzz, HIGH);
  delay(15000);
  digitalWrite(buzz, LOW);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("POR FAVOR..");
  lcd.setCursor(1, 1);
  lcd.print("TENTE NOVAMENTE");
  delay(3500);
  lcd.clear();

}
//******************************TORTURE2*****************************************//
void torture2()
{
  delay(1000);
  lcd.setCursor(1, 0);
  lcd.print(" ");
  lcd.setCursor(2, 0);
  lcd.print("EAR DRUMS ARE");
  lcd.setCursor(0, 1);
  lcd.print(" PRECIOUS!! ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(" WAIT FOR");
  lcd.setCursor(4, 1);
  lcd.print(" 1 MINUTE");
  digitalWrite(buzz, HIGH);
  delay(55000);
  counterbeep();
  lcd.clear();
  digitalWrite(buzz, LOW);
  lcd.setCursor(2, 0);
  lcd.print("WANT ME TO");
  lcd.setCursor(1, 1);
  lcd.print("REDICULE MORE??");
  delay(2500);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Ha Ha Ha Ha");
  delay(1700);
  lcd.clear();
}
