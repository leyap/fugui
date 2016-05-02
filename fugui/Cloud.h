/*
 *	author: lisper
 *	email: leyapin@gmail.com
 *	time: 2016-04-29
 */

#include <Servo.h>
#include <Arduino.h>

class Cloud:public Servo {
	Servo _servo;
	int _pin;
	int _limitPinL;
	int _limitPinR;
	uint32_t _delayTime;
	uint32_t startTime = 0;

	public:
	int state = 1;
	void attach (int pin, int limitPinL, int limitPinR, uint32_t delayTime=2000); 
	void update();

	private:
	void stop (); 
	void cw (); 
	void ccw (); 

};
