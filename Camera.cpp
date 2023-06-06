#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    moveSpeed = startMoveSpeed;
    turnSpeed = startTurnSpeed;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    walkFront = glm::vec3(0.0f, 0.0f, -1.0f);
    update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
    GLfloat velocity = moveSpeed * deltaTime;
    if (keys[GLFW_KEY_W] == true) {
        position += front * velocity;
    }
    if (keys[GLFW_KEY_S] == true) {
        position -= front * velocity;
    }
    if (keys[GLFW_KEY_A] == true) {
        position -= right * velocity;
    }
    if (keys[GLFW_KEY_D] == true) {
        position += right * velocity;
    }
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    update();
}

glm::mat4 Camera::calculateViewMatrix()
{
    //return  CalculateMatrixLookAt(position,position + front , worldUp);
    return glm::lookAt(position, position + front, up);
}

glm :: mat4 CalculateMatrixLookAt(glm :: vec3 position, glm :: vec3 target, glm :: vec3 upVec){
    glm::vec3 zaxis = glm::normalize(position - target);
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(upVec), zaxis));
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);
    glm::mat4 translation = glm::mat4(1.0f); 
    translation[3][0] = -position.x; 
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;
    return rotation * translation;
}

Camera::~Camera()
{
}

glm::mat4 Camera::CalculateMatrixLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 upVec)
{
    return glm::mat4();
}

void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
   
    right = glm::normalize(glm::cross(front, worldUp));
    walkFront = glm::normalize(glm::cross(worldUp, right ));
    up = glm::normalize(glm::cross(right, front));
}
