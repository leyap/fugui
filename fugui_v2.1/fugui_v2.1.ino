/*
 *	author:	lisper
 *	email:	leyapin@gmail.com
 *	time:	2016-05-09
 */

#include "lispStepper.h"

#define NUM 10
#define MAX_DIST (56000)
//#define MAX_DIST 2000

#define CMD_SIZE 6
char cmdbuf[CMD_SIZE];

boolean isRunning = true;

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
	Serial.begin (115200);
	for (int i=0; i<NUM; i++) {
		//steppers[i].forward(random (0, 1000));
		steppers[i].forward(random (0, MAX_DIST/10));
		steppers[i].setMaxDist (MAX_DIST);
	}
	delay (10000);
}

//
void loop () {
	readCmd ();
	if (isRunning) {
		update ();
	}
}

//
void update () {
	static uint32_t lastTime;
	if (millis () - lastTime > 1) {
		lastTime = millis();
		for (int i=0; i<NUM; i++) {
			steppers[i].update();
		}
	}
	//delay (1);
}

//
void readCmd () {
	if (Serial.available ()) {
		int c = Serial.read ();
		if (c == '$') {
			int leng = Serial.readBytesUntil('\r', cmdbuf, CMD_SIZE);
			printStrBuf (cmdbuf, leng);
			if (leng == CMD_SIZE) {
				parseCmd (cmdbuf);
			} 
			else {
				Serial.println ("error not 6 byte");
				printStrBuf (cmdbuf, leng);
			}

		}  
	}
}

//
void printStrBuf (char *buf, int leng) {
	Serial.print("cmdbuf:");
	Serial.print(leng);
	Serial.print(" = ");
	for (int i=0; i < leng; i++) {
		Serial.print (buf[i]);
	}        
}

//
void setAllState(boolean state) {
	for (int i=0; i<NUM; i++) {
		steppers[i].setRunState(state);
	}
}

//
void setOneState(int num, boolean state) {
	steppers[num].setRunState(state);
}

//
void setAllReset () {
	for (int i=0; i<NUM; i++) {
		steppers[i].reset();
	}
}

//
void setOneReset (int num) {
	steppers[num].reset();
}

//
void setAllGoDir (int dir) {
	for (int i=0; i<NUM; i++) {
		steppers[i].go(dir);
	}
}

//
void setOneGoDir (int num, int dir) {
	steppers[num].go(dir);
}

//
void allToZero() {
	for (int i=0; i<NUM; i++) {
		steppers[i].toZero();
	}
}

//
void oneToZero(int num) {
	steppers[num].toZero();
}

//
void parseCmd (char *cmdstring) {
	uint8_t cmd = 0;
	int8_t num = 0;
	int8_t value = 0;

	xtods (cmdstring, CMD_SIZE);
	cmd = cmdstring[0]*16 + cmdstring[1];
	num = cmdstring[2]*16 + cmdstring[3];
	value = cmdstring[4]*16 + cmdstring[5];

	//Serial.println ();
	//Serial.print (cmd);
	//Serial.print (" ");
	//Serial.print (num);
	//Serial.print (" ");
	//Serial.println (value);

	switch (cmd) {
		case 0x10:	//set all run state
			setAllState((boolean)value);
			break;
		case 0x11:	//set one run state
			setOneState(num, (boolean)value);
			break;
		case 0x12:
			setAllReset();
			break;
		case 0x13:	//set one reset
			setOneReset(num);
			break;
		case 0x14:	//set all go with dir
			setAllGoDir(value);
			break;
		case 0x15:	//set one go with dir
			setOneGoDir(num, value);
			break;
		case 0x16:	//all to zero
			allToZero();
			break;
		case 0x17:	//one to zero
			oneToZero(num);
			break;
		default :
			Serial.println ("unknow command");
	}
}

//
void xtods (char *s, int leng) {
	for (int i=0; i<leng; i++) {
		s[i] = xtod (s[i]);
	}
}

//
char xtod (char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return c - 'A'+ 10; 
}


