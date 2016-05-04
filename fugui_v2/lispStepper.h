/*
 *	author:	lisper
 *	email:	leyapin@gmail.com
 *	time:	2016-05-05
 */


#include <Arduino.h>

//
class lispStepper {
		int count;
		int totalNum;
		int currNum;
		int _p1, _p2, _p3, _p4;
		boolean dir;
		boolean finish;
		int state;
		uint32_t lastTime;
		uint32_t delayTime;

	public:
		//
		lispStepper (int p1, int p2, int p3, int p4); 

		//
		void forward(int step); 

		//
		void backward(int step); 

		//
		void setdir(int dir); 

		//
		void setStep(int step); 

		//
		void update (); 

	private:
		//
		void set (int n); 

		//
		void stepUpdate (); 
};

