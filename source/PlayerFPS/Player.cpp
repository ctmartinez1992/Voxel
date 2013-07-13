#include "Player.h"

Player::Player(glm::vec3 position) : _position(position), _movementSpeed(15), _mouseSensitivity(0.1) 
{
	sprintf(_name, "Default");
	_camera = new Camera(position);
	_inputHandler = InputHandler::getInstance();
}

Player::~Player() {
	delete _camera;
	delete _inputHandler;
}

void Player::update(float secondsElapsed) {
	if(_inputHandler->keyPressed(_inputHandler->moveBack)) {
        _camera->offsetPosition(secondsElapsed * _movementSpeed * -_camera->forward());
    } 
	if(_inputHandler->keyPressed(_inputHandler->moveForward)) {
        _camera->offsetPosition(secondsElapsed * _movementSpeed * _camera->forward());
    }
    if(_inputHandler->keyPressed(_inputHandler->moveLeft)) {
        _camera->offsetPosition(secondsElapsed * _movementSpeed * -_camera->right());
    } 
	if(_inputHandler->keyPressed(_inputHandler->moveRight)) {
        _camera->offsetPosition(secondsElapsed * _movementSpeed * _camera->right());
    }
	if(_inputHandler->keyPressed(_inputHandler->moveDown)) {
        _camera->offsetPosition(secondsElapsed * _movementSpeed * -glm::vec3(0,1,0));
    } 
	if(_inputHandler->keyPressed(_inputHandler->moveUp)){
        _camera->offsetPosition(secondsElapsed * _movementSpeed * glm::vec3(0,1,0));
    }

    //rotate camera based on mouse movement
    int mouseX, mouseY;
	_inputHandler->getMousePosition(mouseX, mouseY);
    _camera->offsetOrientation(_mouseSensitivity * mouseY, _mouseSensitivity * mouseX);
    _inputHandler->setMousePosition(0, 0);
}

void Player::render() {

}

void Player::setPosition(const glm::vec3& position) {
    _position = position;
}

const glm::vec3& Player::getPosition() const {
    return _position;
}