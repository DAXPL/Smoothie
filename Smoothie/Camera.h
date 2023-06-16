#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Transform.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>


#include "Shader.h"

class Camera: public Transform
{
public:
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width{800};
	int height{600};

	float speed{1.0f};
	float sensitivity{100.0f};

	Camera(int _width, int _height, glm::vec3 _pos, float _speed, float _sens);
	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);
	void HandleInput(GLFWwindow* window);
private:
	bool IsMouseOverWindow(double& x, double& y);
};