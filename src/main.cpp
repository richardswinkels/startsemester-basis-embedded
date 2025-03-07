#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Dit is tekst...");
}

void loop() {
  Serial.println("Dit blijft maar gaan...");
}
