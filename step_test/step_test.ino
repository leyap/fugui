/*
 *	author:	lisper
 *	email:	leyapin@gmail.com
 */

uint8_t steps[4][4] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
};

uint32_t step_index = 0;

void setup() {
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);
}

void loop () {
	digitalWrite(step_index+2, 1);
	delay (2);
	digitalWrite(step_index+2, 0);
	step_index --;
	if (step_index == 4) {
		step_index = 0;
	} else if (step_index == -1) {
		step_index = 3;
	}
}

/*
void loop() {
	for(int i=2;i<6;i++) {
		digitalWrite(i,1);
		delay(2);
		digitalWrite(i,0); 
	}
}


*/
