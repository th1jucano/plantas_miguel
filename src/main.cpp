#include <Arduino.h>
#include <RTClib.h>


#define rele 5
#define sensorUmidade A0
#define sensorChuva 2

RTC_DS3231 rtc;

void setup() {
  pinMode(rele, OUTPUT);
  pinMode(sensorUmidade, INPUT);
  pinMode(sensorChuva, INPUT_PULLUP);
  digitalWrite(rele, HIGH); // Relé começa desligado
  Serial.begin(9600);
  rtc.begin();
}

void loop() {

  DateTime agora = rtc.now();
  int horaAtual = agora.hour();
  Serial.println(horaAtual);
  bool semChuva = digitalRead(sensorChuva);     // 1 = seco, 0 = chovendo
  int secura = analogRead(sensorUmidade);       // >600 = seco

  if ((horaAtual > 7) || (horaAtual < 17)){

    Serial.print("Sensor de chuva: ");
    Serial.println(semChuva);
    Serial.print("Umidade do solo: ");
    Serial.println(secura);

    if (!semChuva) {
      // Está chovendo → não irrigar
      digitalWrite(rele, HIGH);
      Serial.println("Chovendo — irrigacao bloqueada!");
    }
    else if (secura > 600) {
      // Solo seco e sem chuva → irrigar
      digitalWrite(rele, LOW);
      Serial.println("Solo seco e sem chuva — irrigando...");
    }
    else {
      // Solo úmido → não irrigar
      digitalWrite(rele, HIGH);
      Serial.println("Solo úmido — sem irrigacaoo.");
    }

    Serial.print("Relé esto em: ");
    Serial.println(digitalRead(rele));
    delay(1000);
  }

} 