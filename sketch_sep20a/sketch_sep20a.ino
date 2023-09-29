#define led1 3
#define led2 2
#define timer1 4
#define timer2 5
#define buz 6
#define rele 12

int delai = 0;
int lgd, chu;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(timer2, INPUT);
  pinMode(timer1, INPUT);
  pinMode(buz, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalRead(timer1);
  while (!digitalRead(timer1)) {
    Serial.println(digitalRead(timer1));
    delay(1);
    delai += 1;

    if (delai >= 2000) {
      digitalWrite(rele, HIGH);

      for (int i = 0; i < 3; i++) {
        tone(8, 330, 8000);
        digitalWrite(buz, HIGH);
        delay(100);
        digitalWrite(buz, LOW);
        delay(100);
      }

      unsigned long startTime = millis();
        while (millis() - startTime < 180000) {
          digitalWrite(led1, HIGH);
          delay(500);
          digitalWrite(led1, LOW);
          delay(500);
    }

      for (int i = 0; i < 3; i++) {
        digitalWrite(led1, HIGH);
        delay(500);
        digitalWrite(led1, LOW);
        delay(500);
      }

      digitalWrite(rele, LOW);
      delai = 0;
    }

    while (!digitalRead(timer2)) {
      // ... (restante do código, conforme você desejar)
    }
  }
}
