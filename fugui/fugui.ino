/*
author: lisper
email: leyapin@gmail.com
time: 2016-04-29
*/

#include <Servo.h>
#include "Cloud.h"

#define NUM  5


Cloud clouds[NUM];


void setup() {
	// put your setup code here, to run once:
	Serial.begin (9600);

	pinMode(13, OUTPUT);

	clouds[0].attach(2, 7, A0, 2500);
	clouds[1].attach(3, 8, A1, 4000);
	clouds[2].attach(4, 9, A2, 4500);
	clouds[3].attach(5, 10, A3, 3500);
	clouds[4].attach(6, 11, A4, 2000);

	Serial.println ("start....");
}

void loop() {

	for (int i = 0; i < NUM; i++) {
		clouds[i].update();
	}
	blink();
}

void blink () {
	static uint32_t time = 0;
	static int state = 0;
	if (millis () - time > 500) {
		//    for (int i = 0; i < NUM; i++) {
		//      Serial.print (clouds[i].state);
		//    }
		//    Serial.println();
		state = !state;
		time = millis ();
		digitalWrite(13, state);
		//  Serial.println("ok");
	}
}


