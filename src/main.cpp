#include <Arduino.h>

#define rele 5
#define sensorUmidade A0

void setup() {
  pinMode(rele, OUTPUT);
  pinMode(sensorUmidade, INPUT);
  digitalWrite(rele, HIGH); // Começa desligado

  Serial.begin(9600);
}

void loop() {

  //digitalWrite(rele,!(digitalRead(rele)));
  int secura = analogRead(sensorUmidade);
  Serial.print("Umidade do solo: ");
  Serial.println(secura);
  if (secura > 600) {
    digitalWrite(rele, LOW);  // ATIVA o relé (ativo em LOW)
    Serial.println(" - Solo seco! Passango agua");
  } else {
    digitalWrite(rele, HIGH); // DESATIVA o relé
    Serial.println(" - Solo umido! Nao passa agua");
  }

  delay(1000);
  Serial.print("O rele esta em: ");
  Serial.println(digitalRead(rele));

}
