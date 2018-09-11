#ifndef Bouton_H
#define Bouton_H

#include <Arduino.h>
#include <Button.h>

class Bouton {
	private:
		int _led;
		Button _btn;
		int _currentNumber;
		int _okNumber;

	public:
		Bouton(int led, Button btn, int okNumber);
		bool check();
		int getCurrentNumber();
		void on();
		void off();
};

#endif
