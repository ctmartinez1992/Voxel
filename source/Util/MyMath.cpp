#include "MyMath.h"

glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z) {
    return glm::translate(glm::mat4(), glm::vec3(x,y,z));
}

glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z) {
    return glm::scale(glm::mat4(), glm::vec3(x,y,z));
}

int MyMath::constrain(int value, int min, int max) {
	if (value < min) {
		return min;
	} else if (value > max) {
		return max;
	} else {
		return value;
	}
}

float MyMath::constrain(float value, float min, float max) {
	if (value < min) {
		return min;
	} else if (value > max) {
		return max;
	} else {
		return value;
	}
}

int MyMath::floor(float value) {
	int i = (int) value;
	return value >= (float) i ? i : i - 1;
}

int MyMath::floor(double value) {
	int i = (int) value;
	return value >= (double) i ? i : i - 1;
}

int MyMath::min(int n1, int n2) {
	return (n1 > n2) ? n1 : n2;
}

float MyMath::min(float n1, float n2) {
	return (n1 > n2) ? n1 : n2;
}

glm::vec3 MyMath::randomColor(float r, float g, float b, int rR, int rG, int rB) {
	r += ((rR * -1) + (rand() % (int)(rR - (rR * -1) + 1)));
	g += ((rG * -1) + (rand() % (int)(rG - (rG * -1) + 1)));
	b += ((rB * -1) + (rand() % (int)(rB - (rB * -1) + 1)));
	return glm::vec3(r/255.0, g/255.0, b/255.0);
}

glm::vec3 MyMath::randomColor(float r, float g, float b, int R) {
	float random = ((R * -1) + (rand() % (int)(R - (R * -1) + 1)));
	r += random;
	g += random;
	b += random;
	return glm::vec3(r/255.0, g/255.0, b/255.0);
}