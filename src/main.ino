#include <Button.h>
#include <Bouton.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// display stuff
Adafruit_7segment display = Adafruit_7segment();

// Boutons stuff
Button wBtn = Button(5, INPUT_PULLUP);
Button bBtn = Button(7, INPUT_PULLUP);
Button gBtn = Button(9, INPUT_PULLUP);
Button yBtn = Button(11, INPUT_PULLUP);

Bouton white = Bouton(4, wBtn, 2);
Bouton blue = Bouton(6, bBtn, 7);
Bouton green = Bouton(8, gBtn, 3);
Bouton yellow = Bouton(10, yBtn, 4);

// relay stuff
#define RELAY_PIN 12

// flag
bool didBlink = false;

void setup() {
	Serial.begin(115200);
	// relay init
	pinMode(RELAY_PIN, OUTPUT);
	digitalWrite(RELAY_PIN, LOW);
	// display init
	display.begin(0x70);
}

void loop() {
	bool wState = white.check();
	bool bState = blue.check();
	bool gState = green.check();
	bool yState = yellow.check();
	updateDisplay();
	if (gState && bState && yState && wState) unlock();
	else lock();
	delay(50);
}

void updateDisplay() {
	Serial.print(white.getCurrentNumber());
	Serial.print(blue.getCurrentNumber());
	Serial.print(green.getCurrentNumber());
	Serial.println(yellow.getCurrentNumber());
	display.writeDigitNum(0, white.getCurrentNumber());
	display.writeDigitNum(1, blue.getCurrentNumber());
	display.writeDigitNum(3, green.getCurrentNumber());
	display.writeDigitNum(4, yellow.getCurrentNumber());
	display.writeDisplay();
}

void unlock() {
	Serial.println("UNLOCK");
	digitalWrite(RELAY_PIN, HIGH);
	blink(5);
}

void lock() {
	Serial.println("LOCK");
	digitalWrite(RELAY_PIN, LOW);
	didBlink = false;
}

void blink(int count) {
	if (!didBlink) {
		for(int i = 0; i < count; i++) {
			white.on();
			blue.on();
			green.on();
			yellow.on();
			delay(300);
			white.off();
			blue.off();
			green.off();
			yellow.off();
			delay(300);
		}
		didBlink = true;
	}
}
