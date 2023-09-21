------------------------
/ by Gabriel Silva 🤓 /
------------------------

#include <Arduino.h>

const int buttonPin = 2;    // Pino do botão
const int buzzerPin = 3;    // Pino do buzzer
const int ledPin = 4;       // Pino do LED
const int endSwitchPin = 5; // Pino da chave de fim de curso

bool buttonPressed = false;
bool buzzerActive = false;
bool ledActive = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(endSwitchPin, INPUT_PULLUP);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() {
  // Verifica se o botão foi pressionado por 3 segundos
  if (digitalRead(buttonPin) == LOW) {
    delay(3000);  // Espera por 3 segundos
    if (digitalRead(buttonPin) == LOW) {
      buttonPressed = true;
    }
  }

  if (buttonPressed) {
    // Ativa o buzzer para bipar 3 vezes
    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(200);  // Bipa por 200ms
      digitalWrite(buzzerPin, LOW);
      delay(200);  // Pausa de 200ms entre os bips
    }
    buttonPressed = false;
    buzzerActive = true;
  }

  // Verifica se o buzzer está ativo e o LED não
  if (buzzerActive && !ledActive) {
    // Pisca o LED vermelho por 10 segundos
    for (int i = 0; i < 100; i++) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
    buzzerActive = false;
    ledActive = true;
  }

  // Verifica se o LED está ativo e a chave de fim de curso foi acionada
  if (ledActive && digitalRead(endSwitchPin) == LOW) {
    // Ativa o LED verde
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Verifica se o LED está ativo
  if (ledActive) {
    // Ativa o buzzer para bipar 2 vezes
    for (int i = 0; i < 2; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(200);  // Bipa por 200ms
      digitalWrite(buzzerPin, LOW);
      delay(200);  // Pausa de 200ms entre os bips
    }
    ledActive = false;
  }
}
