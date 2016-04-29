/*
 *	author: lisper
 *	email: leyapin@gmail.com
 *	time: 2016-04-29
 */

#include <Servo.h>
#include "Cloud.h"

Cloud clouds[5] = {
	Cloud(2, 7, A0, 2000),
	Cloud(3, 8, A1, 3000),
	Cloud(4, 9, A2, 4000),
	Cloud(5, 10, A3, 2500),
	Cloud(6, 11, A4, 3500)
};

void setup() {
	// put your setup code here, to run once:
	Serial.begin (9600);
}

void loop() {
	static uint32_t time = 0;
	// put your main code here, to run repeatedly:
	for (int i=0; i<5; i++) {
		clouds[i].update();
	}

	if (millis () - time > 500) {
		time = millis ();
		for (int i=0; i<5; i++) {
			Serial.print (i);
			Serial.print (" -> ");
			Serial.print (clouds[i].state);
			Serial.println ();
		}
		Serial.println ();
	}
}


