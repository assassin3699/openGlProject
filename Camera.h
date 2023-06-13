#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::mat4 calculateViewMatrix();
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	~Camera();

private:
	glm::vec3 up;
	glm::vec3 worldUp;
	glm::vec3 walkFront;
	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	glm::mat4 CalculateMatrixLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 upVec);
	void update();
};



