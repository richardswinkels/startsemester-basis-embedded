#include <Arduino.h>

#define LED_RED 4

void setup()
{
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
}

void loop()
{
  digitalWrite(LED_RED, HIGH);
  delay(500);
  Serial.println(millis());
  digitalWrite(LED_RED, LOW); 
  delay(500);
  Serial.println(millis());
}