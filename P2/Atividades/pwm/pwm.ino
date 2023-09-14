const int ledPin = 13;
const int analogPin = 3;

int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(analogPin);
  
  analogWrite(ledPin, val / 4);
  Serial.println(val);
}
