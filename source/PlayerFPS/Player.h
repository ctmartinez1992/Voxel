#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "../IO/InputHandler.h"

class Player {
	/*************** Variables ***************/
private:
	//Player's name.
	char						_name[100];

	//Position in the world.
	glm::vec3					_position;

	//Handles all the input for the player.
	InputHandler*				_inputHandler;

	//Attributes
	float						_movementSpeed;
	float						_mouseSensitivity;

public:
	//Handles the camera (what the player sees).
	Camera*						_camera;

	/*************** Methods ***************/
public:
	Player(glm::vec3 position);
	~Player();

	//Updates based on the timePassed in a tick.
	void update(float secondsElapsed);

	//Renders the player (if necessary).
	void render();
	
	void						setPosition(const glm::vec3& position);
	const glm::vec3&			getPosition() const;
};

#endif
