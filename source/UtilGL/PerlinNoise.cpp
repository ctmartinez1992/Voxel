#include "PerlinNoise.h"

long* PerlinNoise::_perlin = new long[512];

PerlinNoise::PerlinNoise() {
	for (long i(0); i != 512; ++i) {
		_perlin[i] = i;
	}
    shuffleArray(_perlin, 0, 512);
}

PerlinNoise::~PerlinNoise() {
    delete [] _perlin;
}

float PerlinNoise::noise(float x, float y) {
    long floorX = (long) MyMath::floor(x);
    long floorY = (long) MyMath::floor(y);

    long X = floorX & 255;
    long Y = floorY & 255;
    long Z = 0;

    x -= floorX;
    y -= floorY;

    float u = fade(x);
    float v = fade(y);

    long A = _perlin[X] + Y;
    long B = _perlin[X + 1] + Y;

    long AA = _perlin[A] + Z;
    long AB = _perlin[A + 1] + Z;

    long BA = _perlin[B] + Z;
    long BB = _perlin[B + 1] + Z;

    return lerp(0, 
                lerp(v, 
                     lerp(u, 
                          grad(_perlin[AA], x, y, 0), 
                          grad(_perlin[BA], x - 1, y, 0)), 
                     lerp(u, 
                          grad(_perlin[AB], x, y - 1, 0), 
                          grad(_perlin[BB], x - 1, y - 1, 0))),
                lerp(v, 
                     lerp(u, 
                          grad(_perlin[AA + 1], x, y, -1), 
                          grad(_perlin[BA + 1], x - 1, y, -1)), 
                     lerp(u, 
                          grad(_perlin[AB + 1], x, y - 1, -1),
                          grad(_perlin[BB + 1], x - 1, y - 1, -1))));
}

float PerlinNoise::noise(float x, float y, float z) {
	long X = (long) MyMath::floor(x) & 255;
    long Y = (long) MyMath::floor(y) & 255;
    long Z = (long) MyMath::floor(z) & 255;

	x -= (long) MyMath::floor(x);
    y -= (long) MyMath::floor(y);
    z -= (long) MyMath::floor(z);

    double u = fade(x);
	double v = fade(y);
    double w = fade(z);
     
	long A = _perlin[X]+Y;
	long AA = _perlin[A]+Z;
	long AB = _perlin[A+1]+Z;
	long B = _perlin[X+1]+Y;
	long BA = _perlin[B]+Z;
	long BB = _perlin[B+1]+Z;
	
	if (AA < 0) {
		AA = 0;
	}
	if (AB < 0) {
		AB = 0;
	}
	if (BA < 0) {
		BA = 0;
	}
	if (BB < 0) {
		BB = 0;
	}

    return lerp(w, 
		        lerp(v,  
				     lerp(u, 
					      grad(_perlin[AA], x, y, z),
                          grad(_perlin[BA], x-1, y, z)),
                     lerp(u, 
					      grad(_perlin[AB], x, y-1, z),
                          grad(_perlin[BB], x-1, y-1, z))),
                lerp(v, 
				     lerp(u, 
					      grad(_perlin[AA+1], x, y, z-1),
                          grad(_perlin[BA+1], x-1, y, z-1)),
                     lerp(u, 
					      grad(_perlin[AB+1], x, y-1, z-1),
                          grad(_perlin[BB+1], x-1, y-1, z-1))));
}

float PerlinNoise::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float PerlinNoise::grad(long hash, float x, float y, float z) {
    long h = hash & 15;
    float u = h < 8 ? x : y;
	float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void PerlinNoise::shuffleArray(long* array, long lower, long upper) {
	for (long i(lower); i != upper; ++i) {
		long randomValue = rand() % upper + lower;
		array[i] = array[i] + randomValue;
    }
}