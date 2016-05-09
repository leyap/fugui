/*
 *	author:	lisper
 *	email:	leyapin@gmail.com
 *	time:	2016-05-09
 */

#include "lispStepper.h"

#define NUM 10
#define MAX_DIST 2000

lispStepper steppers[NUM] = {
	lispStepper( 4, 5, 6, 7),
	lispStepper( 8, 9,10,11),
	lispStepper(12,13,14,15),
	lispStepper(16,17,18,19),
	lispStepper(20,21,22,23),
	lispStepper(24,25,26,27),
	lispStepper(28,29,30,31),
	lispStepper(32,33,34,35),
	lispStepper(36,37,38,39),
	lispStepper(40,41,42,43)
};

//
void setup() {
	for (int i=0; i<NUM; i++) {
		//steppers[i].forward(random (0, 1000));
		steppers[i].forward(1000);
		steppers[i].setMaxDist (MAX_DIST);
	}
}

uint32_t lastTime;

//
void loop () {
	if (millis () - lastTime > 1) {
		lastTime = millis();
		for (int i=0; i<NUM; i++) {
			steppers[i].update();
		}
	}
	//delay (1);
}

