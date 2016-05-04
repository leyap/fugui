/*
 *	author:	lisper
 *	email:	leyapin@gmail.com
 *	time:	2016-05-05
 */

#include "lispStepper.h"

#define NUM 5

lispStepper steppers[NUM] = {
	lispStepper( 0, 1, 2, 3),
	lispStepper( 4, 5, 6, 7),
	lispStepper( 8, 9,10,11),
	lispStepper(12,13,14,15),
	lispStepper(16,17,18,19)
};

//
void setup() {
	for (int i=0; i<NUM; i++) {
		steppers[i].forward(random (0, 1000));
	}
}

//
void loop () {
	for (int i=0; i<NUM; i++) {
		steppers[i].update();
	}
	delay (2);
}

