#include <QuantumButton.h>

#define SENSOR_BUTTON_PIN D3
#define SENSOR_BUTTON_GND D1
#define SENSOR_BUTTON_VIN D2

Button myButton(SENSOR_BUTTON_PIN);

bool turnOn = false;
int counter = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Quantum Button Library Example");
  Serial.println("Tap and hold for 2 seconds to enable/disable counter");
  Serial.println("Current counter state = Disabled");
  Serial.println("Single taps adds 1 to it, Double adds 5, Triple adds 25 and Long Tap (more half of second) erases counter");

  // Button
  pinMode(SENSOR_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SENSOR_BUTTON_GND, OUTPUT);
  pinMode(SENSOR_BUTTON_VIN, OUTPUT);
  digitalWrite(SENSOR_BUTTON_GND, LOW);
  digitalWrite(SENSOR_BUTTON_VIN, HIGH);

  myButton.attachHold(onHold);
  myButton.setHoldTime(2000);
  myButton.setLongTapTime(500);
}

void onHold()
{
  turnOn = !turnOn;
  Serial.print("Current counter state = ");
  if (turnOn)
  {
    Serial.println("Enabled");
    myButton.attachTap(onTap);
    myButton.attachDoubleTap(on2Tap);
    myButton.attachTripleTap(on3Tap);
    myButton.attachLongTap(onLong);
  }
  else
  {
    Serial.println("Disabled");
    myButton.dettachAll();
    myButton.attachHold(onHold);
  }
}

void onTap()
{
  counter++;
  Serial.println(counter);
}

void on2Tap()
{
  counter+=5;
  Serial.println(counter);
}

void on3Tap()
{
  counter+=25;
  Serial.println(counter);
}

void onLong()
{
  counter=0;
  Serial.println(counter);
}

void loop() {
  myButton.loop();
}
