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

Then subscribe to button events and set pin to INPUT/INPUT_PULLUP mode
```c++
pinMode(SENSOR_BUTTON_PIN);
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

## Documentation

```c++
// Simply creates button object with pin number
Button(uint8_t pin);
// Example:
Button btn(7);

// Creates button object with pin number and choosing active state - can be used if your button gets you LOW when it's pressed
Button(uint8_t pin, bool active_state);
// Example:
Button btn(28, LOW);

// Creates button and subscribes it to single tap callback function
Button(uint8_t pin, void (*onTap)(void));
// Example:
Button btn(19, tap_callback);

// Creates button with all events and active state selection
Button(uint8_t pin, bool active_state, void (*onTap)(void), void (*onDoubleTap)(void), void (*onTripleTap)(void), void (*onLongTap)(void), void (*onHold)(void));
// Example:
Button btn(15, HIGH, callback_tap, callback_2tap, callback_3tap, callback_longtap, callback_hold);


// Attaches callback function to your button
void attachTap(void (*onTap)(void));
void attachDoubleTap(void (*onDoubleTap)(void));
void attachTripleTap(void (*onTripleTap)(void));
void attachLongTap(void (*onLongTap)(void));
void attachHold(void (*onHold)(void));
// Example:
void callback_tap_function() {
    Serial.print("Button pressed!");
}
btn.attachTap(callback_tap_function);

// Also you can attach all callbacks in one code line:
void attachAll(void (*onTap)(void), void (*onDoubleTap)(void), void (*onTripleTap)(void), void (*onLongTap)(void), void (*onHold)(void));
// Example:
 btn.attachAll(callback_tap, callback_2tap, callback_3tap, callback_longtap, callback_hold);
 
// Same for dettaching:
void dettachAll();
void dettachTap();
void dettachDoubleTap();
void dettachTripleTap();
void dettachLongTap();
void dettachHold();
// Example:
btn.dettachAll();

// To make button working you need to add loop function in program loop
void loop();
// Example:
btn.loop();

// You can change active state for button after creating:
void setActiveState(bool active_state);
// Example:
btn.setActiveState(LOW);

// If you button has short or long bouncing you can change it (default value is 30ms)
void setBounceTime(uint16_t _bounce_time);
// Example:
btn.setBounceTime(50);

// If button may be pressed randomly and you dont want to handle it you can change skip tap time value (default is 5ms)
void setSkipTapTime(uint16_t _skip_tap_time);
// Example:
btn.setSkipTapTime(25);

// If you want you button can be pressed twice or 3 times with more delays between presses you can increate MaxDelayBetweenTaps value (default is 300ms, so if you press button, wait 250ms and press it again it will be double click, if you press button, wait half a second and press it again it will be 2 different single clicks)
void setMaxDelayBetweenTaps(uint16_t _delay_between_taps);
// Example:
btn.setMaxDelayBetweenTaps(450);

// You can change time, which will be handles as holding (default is 3000ms)
void setHoldTime(uint16_t hold_time);
// Example:
btn.setHoldTime(1500);

// Also you can change time of long pressing time (default is 750ms)
void setLongTapTime(uint16_t _long_tap_time);
// Example:
btn.setLongTapTime(500);

// And you can change time of single tap (default is 300ms)
void setSingleTapTime(uint16_t _single_tap_time);
// Example:
btn.setSingleTapTime(250);
```

For examples of usage look "examples" folder.

## How to install

* Download library as ZIP Archive
* Open Arduino IDE
* Click Sketch -> Include Library -> Add .ZIP Library...
