#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
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


Servo myservo;
const int redled = 10;
const int greenled = 11;
const int buzz = 8;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte rows = 4;
const byte cols = 3;

char key[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[rows] = {1, 2, 3, 4};
byte colPins[cols] = {5, 6, 7};
Keypad keypad = Keypad(makeKeymap(key), rowPins, colPins, rows, cols);

void setup() {
  lcd.begin(16, 2);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzz, OUTPUT);
  myservo.attach(9); // SERVO ATTACHED
}

void loop() {
  // Your main code logic goes here
  // ...
 myservo.write(90);  // Rotate 90 degrees
  delay(2000);        // Wait for 2 seconds
  myservo.write(0);   // Return to initial position
  delay(2000);        // Wait for 2 seconds
  // Example: Playing a Christmas tune
  playChristmasTune();

  // Example: Displaying "Feliz Natal" on LCD
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Feliz Natal");

  // Example: Rotating the servo motor
//  rotateServo();
}

void playChristmasTune() {
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

void rotateServo() {
  myservo.write(90);  // Rotate 90 degrees
  delay(2000);        // Wait for 2 seconds
  myservo.write(0);   // Return to initial position
  delay(2000);        // Wait for 2 seconds
}
//Programa: Teste de Display LCD 16 x 2
//Autor: MakerHero
 
//Carrega a biblioteca LiquidCrystal
//#include <LiquidCrystal.h>
// 
////Define os pinos que serão utilizados para ligação ao display
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// 
//void setup()
//{
//  //Define o número de colunas e linhas do LCD
//  lcd.begin(16, 2);
//}
// 
//void loop()
//{
//  //Limpa a tela
//  lcd.clear();
//  //Posiciona o cursor na coluna 3, linha 0;
//  lcd.setCursor(3, 0);
//  //Envia o texto entre aspas para o LCD
//  lcd.print("MakerHero");
//  lcd.setCursor(3, 1);
//  lcd.print(" LCD 16x2");
//  delay(5000);
//   
//  //Rolagem para a esquerda
//  for (int posicao = 0; posicao < 3; posicao++)
//  {
//    lcd.scrollDisplayLeft();
//    delay(300);
//  }
//   
//  //Rolagem para a direita
//  for (int posicao = 0; posicao < 6; posicao++)
//  {
//    lcd.scrollDisplayRight();
//    delay(300);
//  }
//}
