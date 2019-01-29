#ifndef QuantumButton_h
#define QuantumButton_h

#define DEFAULT_BOUNCE_TIME 30
#define DEFAULT_SKIP_TAP_TIME 5
#define DEFAULT_SINGLE_TAP_TIME 300
#define DEFAULT_LONG_TAP_TIME 750
#define DEFAULT_HOLD_TIME 3000
#define DEFAULT_DELAY_BETWEEN_TAPS 300

#include <inttypes.h>

enum ButtonEvent
{
  None,
  Tap,
  DoubleTap,
  TripleTap,
  LongTap,
  VeryLongTap
};

class Button
{
	public:
		Button(uint8_t pin);
		Button(uint8_t pin, bool active_state);
		Button(uint8_t pin, void (*onTap)(void));
		//Button(uint8_t pin,	void (*onTap)(void), void (*onDoubleTap)(void));
		//Button(uint8_t pin,	void (*onTap)(void), void (*onDoubleTap)(void), void (*onTripleTap)(void));
		//Button(uint8_t pin,	void (*onTap)(void), void (*onDoubleTap)(void), void (*onTripleTap)(void), void (*onLongTap)(void), void (*onHold)(void));
		Button(uint8_t pin, bool active_state, void (*onTap)(void), void (*onDoubleTap)(void), void (*onTripleTap)(void), void (*onLongTap)(void), void (*onHold)(void));
    
		void attachTap(void (*onTap)(void));
		void attachDoubleTap(void (*onDoubleTap)(void));
		void attachTripleTap(void (*onTripleTap)(void));
		void attachLongTap(void (*onLongTap)(void));
		void attachHold(void (*onHold)(void));
		void attachAll(void (*onTap)(void), void (*onDoubleTap)(void), void (*onTripleTap)(void), void (*onLongTap)(void), void (*onHold)(void));
		void dettachAll();
		void dettachTap();
		void dettachDoubleTap();
		void dettachTripleTap();
		void dettachLongTap();
		void dettachHold();
		void setActiveState(bool active_state);
		void setBounceTime(uint16_t _bounce_time);
		void setSkipTapTime(uint16_t _skip_tap_time);
		void setMaxDelayBetweenTaps(uint16_t _delay_between_taps);
		void setHoldTime(uint16_t hold_time);
		void setLongTapTime(uint16_t _long_tap_time);
		void setSingleTapTime(uint16_t _single_tap_time);
		void loop();
  
	private:
		uint8_t process_button();

		uint8_t _pin;
		bool _active_state;
		
		void (*_onTap)(void);
		void (*_on2Tap)(void);
		void (*_on3Tap)(void);
		void (*_onLTap)(void);
		void (*_onHold)(void);
		
		uint32_t tap_time = 0;
		uint8_t logical_state = 0;
		uint16_t bounce_time = DEFAULT_BOUNCE_TIME;
		uint16_t skip_tap_time = DEFAULT_SKIP_TAP_TIME;
		uint16_t single_tap_time = DEFAULT_SINGLE_TAP_TIME;
		uint16_t long_tap_time = DEFAULT_LONG_TAP_TIME;
		uint16_t very_long_tap_time = DEFAULT_HOLD_TIME;
		uint16_t delay_between_taps = DEFAULT_DELAY_BETWEEN_TAPS;
};

#endif