#include <QuantumButton.h>

#define SENSOR_BUTTON_PIN D3
#define SENSOR_BUTTON_GND D1
#define SENSOR_BUTTON_VIN D2

Button myButton(SENSOR_BUTTON_PIN);

void setup()
{
  // Serial 
  Serial.begin(115200);
  Serial.println("Quantum Button Library Example");
  Serial.println("This example just telling you about all buttons events");

  // Button
  pinMode(SENSOR_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SENSOR_BUTTON_GND, OUTPUT);
  pinMode(SENSOR_BUTTON_VIN, OUTPUT);
  digitalWrite(SENSOR_BUTTON_GND, LOW);
  digitalWrite(SENSOR_BUTTON_VIN, HIGH);

  // Subscribe to events
  myButton.attachAll(tap, tap2, tap3, tapLong, hold);
}

void tap()
{
  Serial.println("Tap");
}

void tap2()
{
  Serial.println("Double Tap");
}

void tap3()
{
  Serial.println("Triple Tap");
}

void tapLong()
{
  Serial.println("Long Tap");
}

void hold()
{
  Serial.println("Hold");
}

void loop()
{
  myButton.loop();
}
