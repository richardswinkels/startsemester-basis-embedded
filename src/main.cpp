#include <Arduino.h>

#define LED_RED 4

void setup()
{
  pinMode(LED_RED, OUTPUT);
}

void loop()
{
  digitalWrite(LED_RED, HIGH);
  delay(1000);
  digitalWrite(LED_RED, LOW); 
  delay(1000);
}