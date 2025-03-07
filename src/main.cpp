#include <Arduino.h>

long telling = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(telling);
  telling++;
  delay(1000);
}