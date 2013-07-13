#include "FPS.h"

FPS::FPS(double currentTime) : 
	_lastTime(currentTime), 
	_thisTime(0), 
	_initTime(currentTime), 
	_fps(0), 
	_frameCount(0), 
	_timeInterval(1) 
{
}

FPS::~FPS() {
}

void FPS::update(double currentTime) { 
	if (_timeInterval < 0.1) {
		_timeInterval = 0.1;
	}
	if (_timeInterval > 10.0) {
		_timeInterval = 10.0;
	}
 
	if ((currentTime - _initTime) > _timeInterval) {
		_fps = (double)_frameCount / (currentTime - _initTime);
		_frameCount = 0;
		_initTime = currentTime;
		std::cout << _fps << std::endl;
	} else {
		_frameCount++;
	}
}