#pragma once

#include <glm/glm.hpp>

//FPS camera.
class Camera {
	/*************** Variables ***************/
private:
	glm::vec3					_position;
    float						_horizontalAngle;
    float						_verticalAngle;
    float						_fieldOfView;
    float						_nearPlane;
    float						_farPlane;
    float						_viewportAspectRatio;

	/*************** Methods ***************/
public:
	Camera(glm::vec3 position);
	~Camera();
	
	//A rotation matrix that determines the direction the camera is looking.
	glm::mat4					orientation() const;
	
	//Offsets the cameras orientation.							
	void						offsetOrientation(float upAngle, float rightAngle);

	//A unit vector representing the direction the camera is facing.
    glm::vec3					forward() const;

	//A unit vector representing the direction to the right of the camera.
	glm::vec3					right() const;

	//A unit vector representing the direction out of the top of the camera.
	glm::vec3					up() const;

	//The combined camera transformation matrix, including perspective projection.
	glm::mat4					matrix() const;
	
	void						setPosition(const glm::vec3& position);
	void						offsetPosition(const glm::vec3& offset);
	const glm::vec3&			position() const;

    void						setFieldOfView(float fieldOfView);
	float						fieldOfView() const;

	void						setNearAndFarPlanes(float nearPlane, float farPlane);
	float						nearPlane() const;
	float						farPlane() const;

    void						setViewportAspectRatio(float viewportAspectRatio);
    float						viewportAspectRatio() const;
};
