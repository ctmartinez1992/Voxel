#ifndef FPS_H
#define FPS_H

#include <iostream>

class FPS {
	/*************** Variables ***************/
public:
	//Counters for the calculation of the FPS.
	double					_lastTime;
	double					_thisTime;
	double					_initTime;	
	double					_fps;
	int						_frameCount;
	float					_timeInterval;

	/*************** Methods ***************/
public:
	FPS(double currentTime);
	~FPS();

	//Updates the FPS based on the current time.
	void					update(double currentTime);
};

#endif
