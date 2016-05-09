/*
 *	author:	lisper
 *	email:	leyapin@gmail.com
 *	time:	2016-05-05
 */

#include <Arduino.h>
#include "lispStepper.h"

int steps[9][4] = {
	{0,0,0,1},
	{0,0,1,1},
	{0,0,1,0},
	{0,1,1,0},
	{0,1,0,0},
	{1,1,0,0},
	{1,0,0,0},
	{1,0,0,1},
	{0,0,0,0}
};

//
lispStepper::lispStepper (int p1, int p2, int p3, int p4) {
	_p1 = p1;
	_p2 = p2;
	_p3 = p3;
	_p4 = p4;
	dir = 1;
	finish = false;
	state = 1;
	pinMode(_p1, OUTPUT);
	pinMode(_p2, OUTPUT);
	pinMode(_p3, OUTPUT);
	pinMode(_p4, OUTPUT);
	delayTime = random (500, 3000);
}

//
void lispStepper::set (uint32_t n) {
	digitalWrite(_p1, steps[n][0]);
	digitalWrite(_p2, steps[n][1]);
	digitalWrite(_p3, steps[n][2]);
	digitalWrite(_p4, steps[n][3]);
}

//
void lispStepper::forward(uint32_t step) {
	dir = 1;
	totalNum = step;
	finish = false;
}

//
void lispStepper::backward(uint32_t step) {
	dir = 0;
	totalNum = step;
	finish = false;
}

//
void lispStepper::setdir(int dir) {
	this->dir = dir;
}

void lispStepper::setStep(uint32_t step) {
	totalNum = step;
	finish = false;
	if (totalNum > currNum) {
		dir = 1;
	} else {
		dir = 0;
	}
}

//
void lispStepper::update () {
	//static uint32_t maxDist = 42000;
	switch (state) {
		case 1:	//check and cw
			if (millis() - lastTime > delayTime) {
				state ++;
				setStep(random (0, maxDist/2));
				//setStep(random (0, 1));
			}
			break;
		case 2:	//cw
			if (finish) {
				state ++;
				lastTime = millis();
				delayTime = random (500, 3000);
			} else {
				stepUpdate();
			}
			break;
		case 3:	//check and ccw
			if (millis() - lastTime > delayTime) {
				state ++;
				setStep(random (maxDist/2, maxDist));
				//setStep(random (maxDist-1, maxDist));
			}
			break;
		case 4:	//ccw
			if (finish) {
				state = 1;
				lastTime = millis();
				delayTime = random (500, 3000);
			} else {
				stepUpdate();
			}
			break;
	}
}

//
void lispStepper::stepUpdate () {
	if (currNum == totalNum) {
		set(8);
		finish = true;
	} else {
		set(count);
		if (dir) {
			count ++;
			currNum ++;
			if (count == 8) {
				count = 0;
			}
		} else {
			count --;
			currNum --;
			if (count == -1) {
				count = 7;
			}
		}
	}
}

//
void lispStepper::setMaxDist (uint32_t maxDist) {
	this->maxDist = maxDist;
}

