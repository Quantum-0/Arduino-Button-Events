#include "QuantumButton.h"

#include <inttypes.h>
#include "Arduino.h"

// BS -button states
#define BS_RELEASED 0
#define BS_TAP1_PRESSING_BEGIN 1
#define BS_TAP1_PRESSING_END 2
#define BS_TAP1_RELEASING_BEGIN 3
#define BS_TAP1_RELEASING_END 4
#define BS_TAP2_PRESSING_BEGIN 5
#define BS_TAP2_PRESSING_END 6
#define BS_TAP2_RELEASING_BEGIN 7
#define BS_TAP2_RELEASING_END 8
#define BS_TAP3_PRESSING_BEGIN 9
#define BS_TAP3_PRESSING_END 10
#define BS_TAP3_RELEASING_BEGIN 11
#define BS_TAP3_RELEASING_END 12
#define BS_LONG_TAP 13
#define BS_HOLD 14
#define BS_HOLDED_WAIT_FOR_RELEASING 15

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
	_active_state = HIGH;
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
	_onTap = NULL;
	_on2Tap = NULL;
	_on3Tap = NULL;
	_onLTap = NULL;
	_onHold = NULL;
}

void Button::dettachTap()
{
	_onTap = NULL;
}

void Button::dettachDoubleTap()
{
	_on2Tap = NULL;
}

void Button::dettachTripleTap()
{
	_on3Tap = NULL;
}

void Button::dettachLongTap()
{
	_onLTap = NULL;
}

void Button::dettachHold()
{
	_onHold = NULL;
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
  bool pin_state = digitalRead(_pin) == _active_state;
  unsigned long current_time = millis();
  if (pin_state == LOW && logical_state == BS_HOLDED_WAIT_FOR_RELEASING)
  {
	  logical_state = BS_RELEASED;
  }
  else if (pin_state == HIGH && logical_state == BS_RELEASED)
  {
    logical_state = BS_TAP1_PRESSING_BEGIN;
    tap_time = current_time;
  }
  else if ((pin_state == LOW && current_time - tap_time > delay_between_taps) || current_time - tap_time > delay_between_taps + very_long_tap_time)
  {
    ButtonEvent result = None;
    if (logical_state == BS_TAP1_RELEASING_END)
      result = Tap;
    else if (logical_state == BS_TAP2_RELEASING_END)
      result = DoubleTap;  
    else if (logical_state == BS_TAP3_RELEASING_END)
      result = TripleTap;
    else if (logical_state == BS_LONG_TAP)
      result = LongTap;
    else if (logical_state == BS_HOLD)
      result = VeryLongTap;
    logical_state = BS_HOLDED_WAIT_FOR_RELEASING;
    return result;
  }
  else if (current_time - tap_time > bounce_time)
  {
    if (logical_state == BS_TAP1_PRESSING_BEGIN)
      logical_state = BS_TAP1_PRESSING_END;
    else if (logical_state == BS_TAP1_RELEASING_BEGIN)
      logical_state = BS_TAP1_RELEASING_END;
    else if (logical_state == BS_TAP2_PRESSING_BEGIN)
      logical_state = BS_TAP2_PRESSING_END;
    else if (logical_state == BS_TAP2_RELEASING_BEGIN)
      logical_state = BS_TAP2_RELEASING_END; // Кнопка отпущена второй раз
    else if (logical_state == BS_TAP3_PRESSING_BEGIN)
      logical_state = BS_TAP3_PRESSING_END; // Кнопка нажата второй раз
    else if (logical_state == BS_TAP3_RELEASING_BEGIN)
      logical_state = BS_TAP3_RELEASING_END; // Кнопка отпущена второй раз
  }
  if (logical_state == BS_TAP1_PRESSING_END)
  {
    if (pin_state == LOW)
    {
      if (current_time - tap_time < skip_tap_time)
        logical_state = BS_RELEASED; // Fake tap
      else if (current_time - tap_time < single_tap_time)
      {
        logical_state = BS_TAP1_RELEASING_BEGIN; // Отпускание кнопки
        tap_time = current_time;
      }
    }
    else if (current_time - tap_time > long_tap_time)
    {
      logical_state = BS_LONG_TAP;
    }
  }
  else if (logical_state == BS_LONG_TAP)
  {
    if (current_time - tap_time > very_long_tap_time)
      logical_state = BS_HOLD;
  }
  else if (pin_state == HIGH && logical_state == BS_TAP1_RELEASING_END)
  {
    logical_state = BS_TAP2_PRESSING_BEGIN;
    tap_time = current_time;      
  }
  else if (pin_state == LOW && logical_state == BS_TAP2_PRESSING_END)
  {
    logical_state = BS_TAP2_RELEASING_BEGIN;
    tap_time = current_time;
  }
  else if (pin_state == HIGH && logical_state == BS_TAP2_RELEASING_END)
  {
    logical_state = BS_TAP3_PRESSING_BEGIN;
    tap_time = current_time;      
  }
  else if (pin_state == LOW && logical_state == BS_TAP3_PRESSING_END)
  {
    logical_state = BS_TAP3_RELEASING_BEGIN;
    tap_time = current_time;
  }
  
  return None;
}

void Button::loop()
{
	switch(process_button())
	{
		case Tap:
			if (_onTap)
				_onTap();
			break;
		case DoubleTap:
			if (_on2Tap)
				_on2Tap();
			break;
		case TripleTap:
			if (_on3Tap)
				_on3Tap();
			break;
		case LongTap:
			if (_onLTap)
				_onLTap();
			break;
		case VeryLongTap:
			if (_onHold)
				_onHold();
			break;
	}
}