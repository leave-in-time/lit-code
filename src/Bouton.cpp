#include <Bouton.h>

Bouton::Bouton(int led, Button btn, int okNumber) : _led(led), _btn(btn), _okNumber(okNumber) {
	pinMode(_led, OUTPUT);
	digitalWrite(_led, LOW);
	_currentNumber = 0;
}

bool Bouton::check() {
	if (_btn.uniquePress()) {
		_currentNumber++;
		if (_currentNumber > 9) _currentNumber = 0;
	}
	if (_btn.isPressed()) digitalWrite(_led, HIGH);
	else digitalWrite(_led, LOW);
	if (_currentNumber == _okNumber) return true;
	else return false;
}

int Bouton::getCurrentNumber() {
	return _currentNumber;
}

void Bouton::on() {
	digitalWrite(_led, HIGH);
}

void Bouton::off() {
	digitalWrite(_led, LOW);
}
