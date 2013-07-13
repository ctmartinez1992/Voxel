#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

Camera::Camera(glm::vec3 position) : _position(position), _horizontalAngle(0), _verticalAngle(0), _fieldOfView(50),
				   _nearPlane(0.01), _farPlane(100), _viewportAspectRatio(4.0/3.0) 
{
}

Camera::~Camera() {
}

glm::mat4 Camera::orientation() const {
    glm::mat4 orientation;
    orientation = glm::rotate(orientation, _verticalAngle, glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, _horizontalAngle, glm::vec3(0,1,0));
    return orientation;
}

void Camera::offsetOrientation(float upAngle, float rightAngle) {
    _horizontalAngle += rightAngle;
    while(_horizontalAngle > 360.0f) {
		_horizontalAngle -= 360.0;
	}
    while(_horizontalAngle < 0.0f) {
		_horizontalAngle += 360.0;
	}

    _verticalAngle += upAngle;
    if(_verticalAngle > MaxVerticalAngle) {
		_verticalAngle = MaxVerticalAngle;
	}
    if(_verticalAngle < -MaxVerticalAngle) {
		_verticalAngle = -MaxVerticalAngle;
	}
}

glm::vec3 Camera::forward() const {
    glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0,0,-1,1);
    return glm::vec3(forward);
}

glm::vec3 Camera::right() const {
    glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1,0,0,1);
    return glm::vec3(right);
}

glm::vec3 Camera::up() const {
    glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0,1,0,1);
    return glm::vec3(up);
}

glm::mat4 Camera::matrix() const {
    glm::mat4 camera = glm::perspective(_fieldOfView, _viewportAspectRatio, _nearPlane, _farPlane);
    camera *= orientation();
    camera = glm::translate(camera, -_position);
    return camera;
}

void Camera::setPosition(const glm::vec3& position) {
    _position = position;
}

void Camera::offsetPosition(const glm::vec3& offset) {
    _position += offset;
}

const glm::vec3& Camera::position() const {
    return _position;
}

void Camera::setFieldOfView(float fieldOfView) {
    assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
    _fieldOfView = fieldOfView;
}

float Camera::fieldOfView() const {
    return _fieldOfView;
}

void Camera::setNearAndFarPlanes(float nearPlane, float farPlane) {
    assert(nearPlane > 0.0f);
    assert(farPlane > nearPlane);
    _nearPlane = nearPlane;
    _farPlane = farPlane;
}

float Camera::nearPlane() const {
    return _nearPlane;
}

float Camera::farPlane() const {
    return _farPlane;
}

void Camera::setViewportAspectRatio(float viewportAspectRatio) {
    assert(viewportAspectRatio > 0.0);
    _viewportAspectRatio = viewportAspectRatio;
}

float Camera::viewportAspectRatio() const {
    return _viewportAspectRatio;
}
