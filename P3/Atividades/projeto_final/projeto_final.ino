#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

//rfid
#define RST_PIN         7          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


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

//teclado
char key[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[rows] = {21, 22, 23, 24};
byte colPins[cols] = {25, 26, 27};
Keypad keypad = Keypad(makeKeymap(key), rowPins, colPins, rows, cols);

//aleatorio
char password[10] = "4567";
int currentposition = 0;
int invalidcount = 12;



void setup()
{
  displayscreen();
  Serial.begin(9600);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzz, OUTPUT);
  myservo.attach(9); //SERVO ATTACHED//

  lcd.begin(16, 2);

  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop()
{
  if ( currentposition == 0)
  {
    displayscreen();

  }
  int l ;
  char code = keypad.getKey();
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
      if (currentposition == 4)
      {



        unlockdoor();
        currentposition = 0;

      }

    }

    else
    {
      ++invalidcount;
      incorrect();
      currentposition = 0;

    }
    if (invalidcount == 5)
    {

      ++invalidcount;
      torture1();

    }
    if (invalidcount == 8)
    {
      torture2();
    }

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
  lcd.println("BEM-VINDO");
  lcd.setCursor(15, 1);
  lcd.println(" ");
  lcd.setCursor(16, 1);
  lcd.println(" ");
  lcd.setCursor(14, 1);
  lcd.println(" ");
  lcd.setCursor(13, 1);
  lcd.println(" ");
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
  lcd.print("CÓDIGO");
  lcd.setCursor(6, 0);
  lcd.print("INCORRETO");
  lcd.setCursor(15, 1);

  lcd.setCursor(13, 1);
  lcd.println(" ");
  Serial.println("CÓDIGO INCORRETO. NÃO AUTORIZADO");
  digitalWrite(redled, HIGH);
  digitalWrite(buzz, HIGH);
  delay(3000);
  lcd.clear();
  digitalWrite(redled, LOW);
  digitalWrite(buzz, LOW);
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



  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz, LOW);
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

  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(200);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
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
  lcd.println("GET IN WITHIN:::");

  lcd.setCursor(4, 1);
  lcd.print("5");
  delay(200);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz, LOW);
  delay(1000);
  //2
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1); //2
  lcd.print("4");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz, LOW);
  delay(1000);
  //3
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1); //3
  lcd.print("3");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz, LOW);
  delay(1000);
  //4
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1); //4
  lcd.print("2");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
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
  lcd.print("LOCKED!");
  delay(440);
}
//*****************************TORTURE1****************************************//
void torture1()
{
  delay(1000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("WAIT FOR ");
  lcd.setCursor(5, 1);
  lcd.print("15 SECONDS");
  digitalWrite(buzz, HIGH);
  delay(15000);
  digitalWrite(buzz, LOW);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("LOL..");
  lcd.setCursor(1, 1);
  lcd.print(" HOW WAS THAT??");
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
