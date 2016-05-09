/*
 *	author:	lisper
 *	email:	leyapin@gmail.com
 *	time:	2016-05-05
 */


#include <Arduino.h>

//
class lispStepper {
		uint32_t count;
		uint32_t totalNum;
		uint32_t currNum;
		int _p1, _p2, _p3, _p4;
		boolean dir;
		boolean finish;
		int state;
		uint32_t lastTime;
		uint32_t delayTime;
		uint32_t maxDist;

	public:
		//
		lispStepper (int p1, int p2, int p3, int p4); 

		//
		void forward(uint32_t step); 

		//
		void backward(uint32_t step); 

		//
		void setdir(int dir); 

		//
		void setStep(uint32_t step); 

		//
		void update (); 

		//
		void setMaxDist (uint32_t maxDist);

	private:
		//
		void set (uint32_t n); 

		//
		void stepUpdate (); 
};

