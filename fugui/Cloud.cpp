/*
 *	author: lisper
 *	email: leyapin@gmail.com
 *	time: 2016-04-29
 */

#include <Servo.h>
#include <Arduino.h>
#include "Cloud.h"

void Cloud::attach (int pin, int limitPinL, int limitPinR, uint32_t delayTime) {
	_pin = pin;
	_limitPinL = limitPinL;
	_limitPinR = limitPinR;
	_delayTime = delayTime;
	pinMode(_limitPinL, INPUT);
	pinMode(_limitPinR, INPUT);
	_servo.attach(_pin);
}

void Cloud::update() {
	switch (state) {
		case 1:	//delay and cw
			if (millis () - startTime > _delayTime ) {
				cw ();
				state = 2;
				startTime = millis();
			}
			break;
		case 2:	//check left
			if (digitalRead (_limitPinL) == 0 || (millis () - startTime > 8000) ) {
				stop();
				state = 3;
				startTime = millis();
			}
			break;
		case 3:	//delay and ccw
			if (millis () - startTime > _delayTime ) {
				state = 4;
				ccw ();
				startTime = millis();
			}
			break;
		case 4:	//check right
			if (digitalRead (_limitPinR) == 0 || (millis () - startTime > 8000) ) {
				stop ();
				state = 1;
				startTime = millis();
			}
			break;

	}
}

void Cloud::stop () {
	_servo.write(93);
}

void Cloud::cw () {
	_servo.write(0);
}

void Cloud::ccw () {
	_servo.write(180);
}

