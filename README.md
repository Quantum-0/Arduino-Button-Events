# Arduino-Button-Events
## Description

This library allows you to easily process next events of connected button to arduino:
- Single tap/click
- Double tap/click
- Triple tap/click
- Long tap/click
- Press and hold for a time

## Usage

Firsly you need to include library
```c++
#include <QuantumButton.h>
```

Then declare button object
```c++
Button myButton(SENSOR_BUTTON_PIN);
```

Then subscribe to button events
```c++
myButton.attachTap(callback_tap);
myButton.attachDoubleTap(callback_double_tap);
```

Then write that functions
```c++
void callback_tap() {
    /* You code here */
}
void callback_double_tap() {
    /* You code here */
}
```

And then add calling loop function of button in your loop function
```c++
void loop() {
    myButton.loop();
}
```

That's all you need to handle this button events!

## How to install

* Download library as ZIP Archive
* Open Arduino IDE
* Click Sketch -> Include Library -> Add .ZIP Library...
