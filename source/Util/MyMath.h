#ifndef MYMATH_H
#define MYMATH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <iostream>

class MyMath {
	/*************** Variables ***************/

	/*************** Methods ***************/
public:
	//Convenience function that returns a translation matrix.
	static glm::mat4				translate(GLfloat x, GLfloat y, GLfloat z);

	//Convenience function that returns a scaling matrix.
	static glm::mat4				scale(GLfloat x, GLfloat y, GLfloat z);

	//Calculates the floor of a float number.
	static int						constrain(int value, int min, int max);

	//Calculates the floor of a double number.
	static float					constrain(float value, float min, float max);
	
	//Calculates the floor of a float number.
	static int						floor(float n);

	//Calculates the floor of a double number.
	static int						floor(double n);

	//Calculates the floor of a float number.
	static int						floor(float n);

	//Calculates the floor of a double number.
	static int						floor(double n);

	//Generates a random color given a color.
	static glm::vec3				randomColor(float r, float g, float b, int rR, int rG, int rB);

	//Generates a random number and adds to every spectrum.
	static glm::vec3				randomColor(float r, float g, float b, int R);
};

#endif