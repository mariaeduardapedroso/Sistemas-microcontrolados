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


// Bibliotecas necessárias
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

// Configuração do módulo RFID
#define RST_PIN 7
#define SS_PIN 53
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Configuração do sensor magnético da tranca
const int SENSOR_PIN = 13;
const int DARK_THRESHOLD = 100;

// Configuração do servo motor
Servo myservo;
const int redled = 10;
const int greenled = 11;
const int buzz = 8;
int pos = 0;

// Configuração do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte rows = 4;
const byte cols = 3;

// Configuração do teclado
const byte qtdLinhas = 4;
const byte qtdColunas = 4;
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte PinosqtdLinhas[qtdLinhas] = {38, 39, 40, 41};
byte PinosqtdColunas[qtdColunas] = {42, 43, 44, 45};
Keypad meuteclado = Keypad(makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);

// Configuração de senha aleatória
int tamanhoSenha = 4;
char password[10] = "4567";
char passwordEscrito[10];
int currentposition = 0;
int invalidcount = 0;
bool portaAberta = false;
byte tagEsperada[] = {0x52, 0x68, 0x50, 0x1B};

// Protótipos das funções
void displayscreen();
void keypress();
void incorrect();
void torture1();
void torture2();
void counterbeep();
void unlockbuzz();

// Função de inicialização
void setup() {
  displayscreen(); // Inicializa o LCD
  Serial.begin(9600); // Inicializa a comunicação serial
  pinMode(redled, OUTPUT); // Configura o LED vermelho como saída
  pinMode(greenled, OUTPUT); // Configura o LED verde como saída
  pinMode(buzz, OUTPUT); // Configura o buzzer como saída
  myservo.attach(9); // Anexa o servo motor
  pinMode(SENSOR_PIN, INPUT_PULLUP); // Configura o pino do sensor magnético

  lcd.begin(16, 2); // Inicializa o LCD

  while (!Serial);    // Aguarda a inicialização da porta serial
  SPI.begin();      // Inicializa o barramento SPI
  mfrc522.PCD_Init();   // Inicializa o módulo RFID
  delay(4);       // Atraso opcional após a inicialização
  mfrc522.PCD_DumpVersionToSerial();  // Exibe detalhes do módulo RFID
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks...")); // Mensagem para escanear PICC

  inicialTune(); // Toca uma melodia inicial
}

bool modoAdmin = false;
int estado = 0;

// Função principal
void loop() {
  if (modoAdmin) {
    estado = 0;
    menu(); // Exibe o menu
    switch (estado) {
      case 1:
        keypress(); // Aguarda a entrada do usuário
        trocarTag(); // Função para trocar a tag
        break;
      case 2:
        keypress(); // Aguarda a entrada do usuário
        trocarSenha(); // Função para trocar a senha
        break;
    }
        if(portaAberta){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.println(" ");
          lcd.setCursor(1, 0);
          lcd.print("Autorizado");
          lcd.setCursor(4, 1);
          lcd.print("BEM-VINDO");
        }
  } else {
    if (portaAberta) {
      int proximidade = digitalRead(SENSOR_PIN);
      if (proximidade == LOW) {
        Serial.println("FECHADO");
        counterbeep(); // Emite um som indicando a proximidade
        inicialTune(); // Toca a melodia inicial
      }
    } else {
      char tecla_pressionada = meuteclado.getKey(); // Verifica se alguma tecla foi pressionada

      if (tecla_pressionada) { // Se alguma tecla foi pressionada
        Serial.print("Tecla pressionada : ");
        Serial.println(tecla_pressionada);
        passwordEscrito[currentposition] = tecla_pressionada;
      }

      if (currentposition == 0) {
        displayscreen(); // Atualiza a tela
      }

      int l ;

      char code = tecla_pressionada;
      if (code != NO_KEY) {
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("SENHA:");
        lcd.setCursor(3, 1);
        for (l = 0; l <= currentposition; ++l) {
          lcd.print("*");
          keypress(); // Aguarda a entrada do usuário
        }
        currentposition = currentposition + 1;

        if (currentposition == tamanhoSenha) {
          bool verificaSenha = true;
          currentposition = 0;
          for (l = 0; l < tamanhoSenha; ++l) {
            if (passwordEscrito[l] != password[l]) {
              // Erro
              Serial.print("ERRO SENHA: ");
              Serial.print(passwordEscrito[l]);
              Serial.print(" != ");
              Serial.println(password[l]);
              verificaSenha = false;
            }
          }

          if (verificaSenha) {
            unlockdoor(); // Abre a porta
            Serial.println("INVALIDO CONTADOR OK");
            Serial.println(invalidcount);
            invalidcount = 0;
          } else {
            invalidcount = invalidcount + 1;
            Serial.println("INVALIDO CONTADOR BAD");
            Serial.println(invalidcount);
            incorrect(); // Feedback de senha incorreta
          }
        }

        if (invalidcount == 4) {
          ++invalidcount;
          torture1(); // Sequência de tortura 1
        }
        if (invalidcount >= 8) {
          torture2(); // Sequência de tortura 2
        }
      }
    }
  }

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Mostra os UID da tag
    Serial.print("UID da Tag:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Comparação do UID com o valor esperado
    if (verificarTag()) {
      Serial.println("Tag correta!");
      keypress(); // Aguarda a entrada do usuário
      modoAdmin = true;
    } else {
      Serial.println("Tag incorreta!");
    }

    delay(1000);  // Evita leituras repetidas muito rápidas
  }
}

// Função para exibir o menu de escolha
void menu() {
  lcd.clear();
  lcd.print("Escolha:");
  lcd.setCursor(0, 2);
  lcd.print("1: Tag 2: Senha");

  char opcao = 0;

  while (opcao != '1' && opcao != '2') {
    opcao = meuteclado.getKey();
  }

  lcd.clear();

  switch (opcao) {
    case '1':
      lcd.print("Trocar Tag");
      estado = 1;
      delay(2000);  // Aguarda por 2 segundos para exibir a mensagem
      break;
    case '2':
      lcd.print("Trocar Senha");
      estado = 2;
      // Chame a função para trocar a senha aqui
      delay(2000);  // Aguarda por 2 segundos para exibir a mensagem
      break;
  }

  lcd.clear();
}

// Função para trocar a senha
void trocarSenha() {
  lcd.clear();
  lcd.print("Nova senha:");
  lcd.setCursor(0, 1);

  byte index = 0;

  while (true) {
    char tecla = meuteclado.getKey();
    if (tecla) {
        keypress();
        
      if (tecla == '#') {
        password[index] = '\0'; // Adiciona o caractere nulo para indicar o final da string
        tamanhoSenha = index;
        break; // Finaliza a entrada da senha
      } 

      if (index < 9) {
        password[index++] = tecla;
        lcd.print('*'); // Máscara para esconder os caracteres digitados
      }else{
        tamanhoSenha = index;
        break; // Finaliza a entrada da senha
      }
    }
  }

  Serial.println(); // Nova linha para melhorar a legibilidade
  lcd.clear();
  lcd.print("Senha alterada!");
  delay(1000);

  Serial.print("Senha alterada para: ");
  Serial.println(password);
  modoAdmin = false;
}

// Função para trocar a tag RFID
void trocarTag() {
  lcd.clear();
  lcd.print("Aproxime cartao:");

  while (!mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
  }

  if (mfrc522.PICC_ReadCardSerial()) {
    for (byte i = 0; i < mfrc522.uid.size && i < sizeof(tagEsperada); i++) {
      tagEsperada[i] = mfrc522.uid.uidByte[i];
    }

    Serial.print("Tag trocada para:");
    
    
    lcd.clear();
    lcd.print("Tag trocada para:");
    lcd.setCursor(0, 1);

    for (byte i = 0; i < sizeof(tagEsperada); i++) {
      lcd.print(tagEsperada[i], HEX);
      Serial.println(tagEsperada[i], HEX);
    }

    delay(2000);  // Aguarda por 2 segundos para exibir a mensagem
    modoAdmin = false;
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// Função para verificar se a tag RFID é válida
bool verificarTag() {
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] != tagEsperada[i]) {
      return false;  // UID não corresponde
    }
  }
  return true;  // UID corresponde
}

// Função para tocar uma melodia inicial
void inicialTune() {
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

// Função para abrir a porta
void unlockdoor() {
  delay(900);

  lcd.setCursor(0, 0);
  lcd.println(" ");
  lcd.setCursor(1, 0);
  lcd.print("Autorizado");
  lcd.setCursor(4, 1);
  lcd.print("BEM-VINDO");

  unlockbuzz();

  for (pos = 90; pos >= 0; pos -= 5) {
    myservo.write(pos);
    delay(5);
  }
  delay(2000);

  portaAberta = true;
}

// Função para lidar com código incorreto
void incorrect() {
  delay(500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("CODIGO");
  lcd.setCursor(1, 1);
  lcd.print("INCORRETO");
  lcd.setCursor(15, 1);

  Serial.println("CÓDIGO INCORRETO. NÃO AUTORIZADO");
  digitalWrite(redled, HIGH);
  tone(buzz, NOTE_E1, 1000);
  delay(500);
  noTone(buzz);
  delay(3000);
  lcd.clear();
  digitalWrite(redled, LOW);
  displayscreen();
}

// Função para limpar a tela do LCD
void clearscreen() {
  lcd.setCursor(0, 0);
  lcd.println(" ");
  lcd.setCursor(0, 1);
  lcd.println(" ");
  lcd.setCursor(0, 2);
  lcd.println(" ");
  lcd.setCursor(0, 3);
  lcd.println(" ");
}

// Função para emitir um som de tecla pressionada
void keypress() {
  tone(buzz, NOTE_C6, 100);
  delay(50);
  noTone(buzz);
}

// Função para exibir a tela inicial no LCD
void displayscreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("*DIGITE A SENHA*");
}

// Função para posicionar o servo
void armservo() {
  for (pos = 180; pos <= 180; pos += 50) {
    myservo.write(pos);
    delay(5);
  }
  delay(5000);

  for (pos = 180; pos >= 0; pos -= 50) {
    myservo.write(pos);
  }
}

// Função para emitir um som de desbloqueio
void unlockbuzz() {
  for (int i = 0; i < 4; i++) {
    tone(buzz, NOTE_C6, 100);
    delay(500);
    noTone(buzz);
  }
}

// Função para contar beeps
void counterbeep() {
  delay(1200);

  lcd.clear();

  lcd.setCursor(2, 0);
  delay(200);
  lcd.print("FECHANDO EM:");
  for (int i = 5; i > 0; i--) {
    lcd.setCursor(7, 1);
    lcd.print("0");
    lcd.print(i);
    keypress();
    delay(1000);
  }

  for (pos = 0; pos <= 90; pos += 5) {
    myservo.write(pos);
  }
  delay(15);

  currentposition = 0;

  lcd.clear();
  displayscreen();

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("FECHADO!");
  delay(440);

  portaAberta = false;
}

// Função de tortura 1
void torture1() {
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

// Função de tortura 2
void torture2() {
  lcd.setCursor(1, 0);
  lcd.print(" ");
  lcd.setCursor(2, 0);
  lcd.print("MUITAS");
  lcd.setCursor(0, 1);
  lcd.print(" TENTATIVAS!! ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("AGUARDE POR ");
  lcd.setCursor(4, 1);
  lcd.print(" 1 MINUTO");
  digitalWrite(buzz, HIGH);
  delay(55000);
  counterbeep();
  lcd.clear();
  digitalWrite(buzz, LOW);
  lcd.setCursor(2, 0);
  lcd.print("TENTE ACERTAR");
  lcd.setCursor(1, 1);
  lcd.print("TA DIFICIL??");
  delay(2500);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Ha Ha Ha Ha");
  delay(1700);
  lcd.clear();
}
