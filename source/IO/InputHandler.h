#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <map>
#include <GL/glfw.h>

class InputHandler {
//Variables
public:
	/*************** Variables ***************/
public:
	//Singleton.
	static InputHandler*			_instance;

	//Mouse
	const int						mouseLeft;
	const int						mouseRight;
	const int						mouseMiddle;

	//Movement
	const int						moveForward;			//W
	const int						moveBack;				//S
	const int						moveLeft;				//A
	const int						moveRight;				//D
	const int						moveUp;					//Q
	const int						moveDown;				//Z

	//A map with all they keys.
	std::map<int, int>				keys;

	/*************** Methods ***************/
public:
	InputHandler();
	virtual ~InputHandler();

	//Get a pointer to the Input Handler from anywhere (Lazy but Safe)
	static InputHandler*			getInstance();

	//Check if a certain key was pressed.
	bool							keyPressed(int key);

	//Check if a certain mouse button was pressed.
	bool							mousePressed(int key) const;

	void							setMouseWheelValue(const float value);
	float							getMouseWheelValue() const;
	void							setMousePosition(const int x, const int y);
	void							getMousePosition(int& x, int& y) const;
};

#endif
