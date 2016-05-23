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
	_loopState = 1;
	pinMode(_p1, OUTPUT);
	pinMode(_p2, OUTPUT);
	pinMode(_p3, OUTPUT);
	pinMode(_p4, OUTPUT);
	delayTime = random (500, 3000);
	runState = true;
}

//set the stepper motor 4-pin state
void lispStepper::set (uint8_t n) {
	digitalWrite(_p1, steps[n][0]);
	digitalWrite(_p2, steps[n][1]);
	digitalWrite(_p3, steps[n][2]);
	digitalWrite(_p4, steps[n][3]);
}

//
void lispStepper::forward(int32_t step) {
	dir = 1;
	totalNum = step;
	finish = false;
}

//
void lispStepper::backward(int32_t step) {
	dir = 0;
	totalNum = step;
	finish = false;
}

//
void lispStepper::setdir(int dir) {
	this->dir = dir;
}

void lispStepper::setStep(int32_t step) {
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
	if (runState == false) {	//not in run
		stepUpdate();
	} else {	//in running	
		switch (_loopState) {
			case 1:	//check and cw
				if (millis() - lastTime > delayTime) {
					_loopState ++;
					setStep(random (0, maxDist));
					//setStep(0);
				}
				break;
			case 2:	//cw
				if (finish) {
					_loopState ++;
					lastTime = millis();
					delayTime = random (500, 3000);
				} else {
					stepUpdate();
				}
				break;
			case 3:	//check and ccw
				if (millis() - lastTime > delayTime) {
					_loopState ++;
					setStep(random (0, maxDist));
					//setStep(maxDist);
				}
				break;
			case 4:	//ccw
				if (finish) {
					_loopState = 1;
					lastTime = millis();
					delayTime = random (500, 3000);
				} else {
					stepUpdate();
				}
				break;
		}
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

//set maxDist
void lispStepper::setMaxDist (int32_t maxDist) {
	this->maxDist = maxDist;
}

//set run state
void lispStepper::setRunState(boolean state) {
	this->runState = state;
	if (state) {
	} else {
		this->setStep(currNum);
	}
}

//get run state
boolean lispStepper::getRunState() {
	return (this->runState);
}

//set currNum to 0
void lispStepper::reset() {
	this->currNum = 0;
	setStep(currNum);
}

//to zero
void lispStepper::toZero() {
	setStep(0);
}

//go a maxDist with dir
boolean lispStepper::go(int dir) {
	if (runState) {
		return false;
	} else {
		if (dir > 0) {
			setStep(currNum + maxDist);
		} else {
			setStep(currNum - maxDist);
		}
		return true;
	}
}


