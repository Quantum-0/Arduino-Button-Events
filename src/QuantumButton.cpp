#include "QuantumButton.h"

#include <inttypes.h>
#include "Arduino.h"

Button::Button(uint8_t pin)
{
	_pin = pin;
	_active_state = HIGH;
}

Button::Button(uint8_t pin, bool active_state)
{
	_pin = pin;
	_active_state = active_state;
}

Button::Button(uint8_t pin, void (*onTap)(void))
{
	_pin = pin;
	_onTap = onTap;
}

Button::Button(uint8_t pin, bool active_state, void (*onTap)(void), void (*onDoubleTap)(void), void (*onTripleTap)(void), void (*onLongTap)(void), void (*onHold)(void))
{
	_pin = pin;
	_active_state = active_state;
	
	_onTap = onTap;
	_on2Tap = onDoubleTap;
	_on3Tap = onTripleTap;
	_onLTap = onLongTap;
	_onHold = onHold;
}
		
void Button::attachAll(void (*onTap)(void), void (*onDoubleTap)(void), void (*onTripleTap)(void), void (*onLongTap)(void), void (*onHold)(void))
{
	_onTap = onTap;
	_on2Tap = onDoubleTap;
	_on3Tap = onTripleTap;
	_onLTap = onLongTap;
	_onHold = onHold;
}

void Button::dettachAll()
{
	_onTap = 0;
	_on2Tap = 0;
	_on3Tap = 0;
	_onLTap = 0;
	_onHold = 0;
}

void Button::dettachTap()
{
	_onTap = 0;
}

void Button::dettachDoubleTap()
{
	_on2Tap = 0;
}

void Button::dettachTripleTap()
{
	_on3Tap = 0;
}

void Button::dettachLongTap()
{
	_onLTap = 0;
}

void Button::dettachHold()
{
	_onHold = 0;
}
void Button::attachTap(void (*onTap)(void))
{
	_onTap = onTap;
}

void Button::attachDoubleTap(void (*onDoubleTap)(void))
{
	_on2Tap = onDoubleTap;
}

void Button::attachTripleTap(void (*onTripleTap)(void))
{
	_on3Tap = onTripleTap;
}

void Button::attachLongTap(void (*onLongTap)(void))
{
	_onLTap = onLongTap;
}

void Button::attachHold(void (*onHold)(void))
{
	_onHold = onHold;
}

void Button::setActiveState(bool active_state)
{
	_active_state = active_state;
}

void Button::setBounceTime(uint16_t _bounce_time)
{
	bounce_time = _bounce_time;
}

void Button::setSkipTapTime(uint16_t _skip_tap_time)
{
	skip_tap_time = _skip_tap_time;
}

void Button::setSingleTapTime(uint16_t _single_tap_time)
{
	single_tap_time = _single_tap_time;
}

void Button::setLongTapTime(uint16_t _long_tap_time)
{
	long_tap_time = _long_tap_time;
}

void Button::setHoldTime(uint16_t hold_time)
{
	very_long_tap_time = hold_time;
}

void Button::setMaxDelayBetweenTaps(uint16_t _delay_between_taps)
{
	delay_between_taps = _delay_between_taps;
}

uint8_t Button::process_button()
{
  bool pin_state = digitalRead(_pin);
  unsigned long current_time = millis();
  if (pin_state == HIGH && logical_state == 0)
  {
    logical_state = 1; // Нажатие кнопки начато
    tap_time = current_time;
  }
  else if ((pin_state == LOW && current_time - tap_time > delay_between_taps) || current_time - tap_time > delay_between_taps + very_long_tap_time)
  {
    ButtonEvent result = None;
    if (logical_state == 4)
      result = Tap;
    else if (logical_state == 8)
      result = DoubleTap;  
    else if (logical_state == 12)
      result = TripleTap;
    else if (logical_state == 13)
      result = LongTap;
    else if (logical_state == 14)
      result = VeryLongTap;
    logical_state = 0;
    return result;
  }
  else if (current_time - tap_time > bounce_time)
  {
    if (logical_state == 1)
      logical_state = 2; // Кнопка нажата
    else if (logical_state == 3)
      logical_state = 4; // Кнопка отпущена
    else if (logical_state == 5)
      logical_state = 6; // Кнопка нажата второй раз
    else if (logical_state == 7)
      logical_state = 8; // Кнопка отпущена второй раз
    else if (logical_state == 9)
      logical_state = 10; // Кнопка нажата второй раз
    else if (logical_state == 11)
      logical_state = 12; // Кнопка отпущена второй раз
  }
  if (logical_state == 2)
  {
    if (pin_state == LOW)
    {
      if (current_time - tap_time < skip_tap_time)
        logical_state = 0; // Обрабатываем как ложное нажатие
      else if (current_time - tap_time < single_tap_time)
      {
        logical_state = 3; // Отпускание кнопки
        tap_time = current_time;
      }
    }
    else if (current_time - tap_time > long_tap_time)
    {
      logical_state = 13;
    }
  }
  else if (logical_state == 13)
  {
    if (current_time - tap_time > very_long_tap_time)
      logical_state = 14;
  }
  else if (pin_state == HIGH && logical_state == 4)
  {
    logical_state = 5; // Второе нажатие начато
    tap_time = current_time;      
  }
  else if (pin_state == LOW && logical_state == 6)
  {
    logical_state = 7; // Второе отпускание начато
    tap_time = current_time;
  }
  else if (pin_state == HIGH && logical_state == 8)
  {
    logical_state = 9; // Третье нажатие начато
    tap_time = current_time;      
  }
  else if (pin_state == LOW && logical_state == 10)
  {
    logical_state = 11; // Третье отпускание начато
    tap_time = current_time;
  }
  
  return None;
}

void Button::loop()
{
	switch(process_button())
	{
		case Tap:
			_onTap();
			break;
		case DoubleTap:
			_on2Tap();
			break;
		case TripleTap:
			_on3Tap();
			break;
		case LongTap:
			_onLTap();
			break;
		case VeryLongTap:
			_onHold();
			break;
	}
}