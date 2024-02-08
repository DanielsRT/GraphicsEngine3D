#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:
	// Camera vectors
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Stop camera from moving on first click
	bool firstClick = true;

	// Window width and height
	int width;
	int height;

	float speed = 0.008f;
	float sensitivity = 100.0f;

	Camera(int width, int height, glm::vec3 position);

	// Sends the camera matrix to the vertex shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Controls camera inputs
	void Inputs(GLFWwindow* window);
};

#endif