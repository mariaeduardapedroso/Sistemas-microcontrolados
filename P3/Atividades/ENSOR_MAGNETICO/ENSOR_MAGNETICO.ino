const int SENSOR_PIN = 13;
const int BUZZER_PIN = 8;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int proximidade = digitalRead(SENSOR_PIN);
  if(proximidade == LOW){
    Serial.println("FECHADO");
    digitalWrite(BUZZER_PIN, LOW);
  }else{
    digitalWrite(BUZZER_PIN, HIGH);    
  }
}
