#include <Arduino.h>
#include <HCSR04.h>

#define p_trig 5
#define p_echo 3
#define buz 8
#define botao 7
#define ENB 2

UltraSonicDistanceSensor distanceSensor(p_trig, p_echo);
const int In3 = 9;
const int In4 = 10;
const int In1 = 6;
const int In2 = 11;
const int Vermelho = 4;
const int Verde = 12;


bool sistemaLigado = false; 
bool ultimoEstadoBotao = HIGH;

void setup() {
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(Vermelho, OUTPUT);
  pinMode(Verde, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  pinMode(ENB, OUTPUT);

  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);

  Serial.begin(9600);
}

void loop() {
  bool estadoBotao = digitalRead(botao);

  if (estadoBotao == LOW && ultimoEstadoBotao == HIGH) {
    sistemaLigado = !sistemaLigado;
    delay(200);
  }
  ultimoEstadoBotao = estadoBotao;

  if (sistemaLigado) {
    float distance = distanceSensor.measureDistanceCm();

    if (distance != -1) {
      Serial.println(distance);
    } else {
      Serial.println("Erro: Sensor de distancia nao conseguiu uma leitura valida.");
    }

    if (distance > 0 && distance <= 30) {
      tone(buz, 320);
      analogWrite(ENB, 220);
      digitalWrite(In3, LOW);
      digitalWrite(In4, HIGH);
      digitalWrite(In1, LOW);
      digitalWrite(In2, HIGH);
      digitalWrite(Vermelho, HIGH);
      digitalWrite(Verde, LOW);
    } else if (distance > 30 && distance <= 40) {

    } else if (distance > 20 && distance <= 100) {
      noTone(buz);
      analogWrite(ENB, 220);
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      digitalWrite(In1, LOW);
      digitalWrite(In2, HIGH);
      digitalWrite(Vermelho, LOW);
      digitalWrite(Verde, HIGH);
    }
  } else {
    noTone(buz);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
  }
}