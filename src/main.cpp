#include <Arduino.h>

#include "Display.h"

#define BTN_LEFT 9
#define BTN_RIGHT 8
#define LED_RED 4
#define LED_GREEN 5
#define BUZZER 3

int correctPin[] = {1, 2, 3, 4};
int inputPin[4];
int currentIndex = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 300;

void printMessage(String message)
{
  Serial.println(message);
}

void displayInputPin()
{
  String pin = "";

  for (int i = 0; i < 4; i++)
  {
    pin += String(inputPin[i]);
  }

  Display.show(pin);
}

void resetSafe()
{
  for (int i = 0; i < 4; i++)
  {
    inputPin[i] = 0;
  }

  currentIndex = 0;

  displayInputPin();
  digitalWrite(LED_RED, HIGH);
  printMessage("Pincode invoeren");
}

void showErrorResponse()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_RED, LOW);
    delay(500);
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER, 500);
    delay(500);
    digitalWrite(LED_RED, LOW);
    noTone(BUZZER);
  }
}

void showSuccessResponse()
{
  printMessage("Veilig open");
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  tone(BUZZER, 500);
  delay(1000);
  digitalWrite(LED_GREEN, LOW);
  noTone(BUZZER);
}

void checkPincode()
{
  printMessage("Pincode ingevoerd, controleren...");
  delay(2000);

  for (int i = 0; i < 4; i++)
  {
    if (inputPin[i] != correctPin[i])
    {
      showErrorResponse();
      resetSafe();
      return;
    }
  }

  showSuccessResponse();
  resetSafe();
}

void handleButtonInputs()
{
  if (digitalRead(BTN_LEFT) == LOW &&
      millis() - lastDebounceTime > debounceDelay)
  {
    lastDebounceTime = millis();
    inputPin[currentIndex] = (inputPin[currentIndex] + 1) % 10;
    displayInputPin();
  }

  if (digitalRead(BTN_RIGHT) == LOW &&
      millis() - lastDebounceTime > debounceDelay)
  {
    lastDebounceTime = millis();

    if (currentIndex == 3)
    {
      checkPincode();
      return;
    }

    currentIndex++;
    displayInputPin();
  }
}

void setup()
{
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  digitalWrite(LED_RED, HIGH);
  printMessage("Pincode invoeren");
  displayInputPin();
}

void loop()
{
  handleButtonInputs();
}