
#include <Arduino.h>

#define ON_OFF_BUTTON_PIN 4
#define BUZZER_PIN 6
#define END_OF_CYCLE_PIN 5
#define LED1_PIN 2
#define LED2_PIN 3
#define RELAY_PIN 12
#define BUZZER_BUS_PIN 8

int delayCounter = 0;
int delayCounter2 = 0;
int delayCounter3 = 0;
int delayCounter4 = 0;
int delayCounter5 = 0;


int j = 0;
int n = 0;
int w = 0;
int x = 0;
int z = 0;
int a = 0;
int b = 0;
int c = 0;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUZZER_BUS_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(END_OF_CYCLE_PIN, INPUT);
  pinMode(ON_OFF_BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void heating() {
  bool onOffButtonState = digitalRead(ON_OFF_BUTTON_PIN);

  if (!onOffButtonState) {
    delayCounter3 = 0;
  }

  digitalWrite(LED2_PIN, HIGH);
  delay(500);
  digitalWrite(LED2_PIN, LOW);
  delay(500);
  delayCounter += 1;

  while (!onOffButtonState && (x + z) > 1) {
    delayCounter3 += 1;
    Serial.println(onOffButtonState);

    if (delayCounter3 >= 2000) {
      j = 0;
      x = 0;
    }
  }
}

void loop2() {
  while (delayCounter >= 4 && n >= 1) {
    bool onOffButtonState = digitalRead(ON_OFF_BUTTON_PIN);

    if (!onOffButtonState) {
      c += 1;
    }

    if (onOffButtonState) {
      c = 0;
    }

    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    bool endOfCycleState = digitalRead(END_OF_CYCLE_PIN);
    delayCounter2 += 1;
    delay(1);
    delayCounter4 = 0;
    delayCounter5 = 0;

    Serial.println(endOfCycleState);

    if (delayCounter2 >= 18000) {
      delayCounter = 0;
      j = 0;
      n = 0;
    }

    if (!endOfCycleState) {
      bip();
      bip();
      w = 0;

      while (!endOfCycleState && w != 1) {
        bool endOfCycleState = digitalRead(END_OF_CYCLE_PIN);
        delayCounter2 = 0;
        delayCounter4 += 1;
        delayCounter5 += 1;
        delay(1);

        Serial.println(endOfCycleState);

        if (endOfCycleState) {
          w = 1;
        }

        if (delayCounter4 >= 6000) {
          bip();

          while (delayCounter4 >= 6000 && w != 1) {
            bool endOfCycleState = digitalRead(END_OF_CYCLE_PIN);
            digitalWrite(LED1_PIN, HIGH);

            if (endOfCycleState) {
              w = 1;
            }
          }
        }

        if (delayCounter5 >= 300000) {
          delayCounter = 0;
          j = 0;
          n = 0;
          w = 1;
        }
      }
    }

    if (c >= 400) {
      delayCounter = 0;
      n = 0;
    }
  }
}

void bip() {
  tone(BUZZER_BUS_PIN, 330, 300);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(BUZZER_PIN, LOW);
  delay(300);
}

void loop() {
  bool onOffButtonState = digitalRead(ON_OFF_BUTTON_PIN);
  bool endOfCycleState = digitalRead(END_OF_CYCLE_PIN);
  x = 1;
  a = 0;
  b = 0;

  if (!onOffButtonState) {
    j += 1;
  }

  if (onOffButtonState) {
    j = 0;
  }

  if (j >= 400) {
    bip();
    b = 1;

    while (j >= 400 && b >= 1) {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println(delayCounter);
      heating();
      delay(1);

      if (delayCounter >= 4) {
        bip();
        bip();
        bip();
        a = 1;

        while (delayCounter >= 4 && a >= 1) {
          n = 1;
          loop2();
        }
      }

      z = 1;
    }
  }

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  delay(1);
}
