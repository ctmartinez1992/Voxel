#include "FPS.h"

FPS::FPS(double currentTime) : 
	_lastTime(currentTime), 
	_thisTime(0), 
	_initTime(currentTime), 
	_fps(0), 
	_frameCount(0), 
	_timeInterval(1),
	_counter(0)
{
}

FPS::~FPS() {
}

void FPS::update(double currentTime) { 
	_timeInterval = MyMath::constrain(_timeInterval, 0.1, 10.0);
 
	if ((currentTime - _initTime) > _timeInterval) {
		_fps = (double)_frameCount / (currentTime - _initTime);
		_frameCount = 0;
		_initTime = currentTime;
		_counter++;
		std::cout << std::endl << _fps << std::endl;
	} else {
		_frameCount++;
	}
}