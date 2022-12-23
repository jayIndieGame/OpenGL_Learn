#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	Cam_Up,
	Cam_DOWN
};

const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED		= 10.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;


class Camera {
private:
	bool firstMouse;
	float lastX = 1280.0/2;
	float lastY = 960.0/2;
	bool m_isOrtho = false;
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	~Camera();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ImGuiMouse(GLFWwindow* window);

private:
	void updateCameraVectors();

};	