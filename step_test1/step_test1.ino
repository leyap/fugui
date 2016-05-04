#include <Stepper.h>

// 这里设置步进电机旋转一圈是多少步
#define STEPS 1600

// attached to设置步进电机的步数和引脚
Stepper stepper(STEPS, 2, 3, 4, 5);


void setup() {
	stepper.setSpeed(100);
}

void loop () {
	stepper.step (0);
	delay (500);
	stepper.step (20000);
	delay (500);
}


