/*
 *	author:	lisper
 *	email:	leyapin@gmail.com
 *	time:	2016-05-05
 */


#include <Arduino.h>

//
class lispStepper {
		uint32_t count;
		int32_t totalNum;
		int32_t currNum;
		int _p1, _p2, _p3, _p4;
		boolean dir;
		boolean finish;
		int _loopState;
		uint32_t lastTime;
		uint32_t delayTime;
		int32_t maxDist;
		boolean runState;

	public:
		//
		lispStepper (int p1, int p2, int p3, int p4); 

		//
		void forward(int32_t step); 

		//
		void backward(int32_t step); 

		//
		void setdir(int dir); 

		//
		void setStep(int32_t step); 

		//
		void update (); 

		//
		void setMaxDist (int32_t maxDist);

		//
		void setRunState(boolean state);

		//
		boolean getRunState();

		//
		void reset();

		//
		boolean go(int dir);

	private:
		//
		void set (uint8_t n); 

		//
		void stepUpdate (); 
};

