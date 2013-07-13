#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "../Util/MyMath.h"
#include <glm/glm.hpp>
#include <iostream>

class PerlinNoise {
	/*************** Variables ***************/
private:
	//Long vector to handle the noise.
	static long*					_perlin;

	/*************** Methods ***************/
public:
	PerlinNoise();
	~PerlinNoise();
	
	//2D noise.
	static float					noise(float x, float y);

	//3D noise.
	static float					noise(float x, float y, float z);

private:
	//Helper methods for the noise making.
	static float					fade(float t);
	static float					lerp(float t, float a, float b);
	static float					grad(long hash, float x, float y, float z);

	//Randomly shuffles the array.
	static void						shuffleArray(long* array, long lower, long upper);
};

#endif