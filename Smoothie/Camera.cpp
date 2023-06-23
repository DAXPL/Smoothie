#include "Camera.h"
//https://www.glfw.org/docs/3.3/group__keys.html
Camera::Camera(int _width, int _height, glm::vec3 _pos, float _speed, float _sens)
{
	width = _width;
	height = _height;
	position = _pos;
	speed = _speed;
	sensitivity = _sens;
}

void Camera::Matrix(Shader& shader, const char* uniform) 
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::HandleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	//Gora
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += speed * up;
	}
	//Dol
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position += speed * -up;
	}
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX{ 0 };
		double mouseY{ 0 };
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (IsMouseOverWindow(mouseX, mouseY)) return;

		float rotX{sensitivity * (float)(mouseY - (height / 2)) / height};
		float rotY{sensitivity * (float)(mouseX - (width / 2))  / width};

		//Obraca gora/dol (pitch?)
		glm::vec3 newOrientation {glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up))) };

		// Ogranicza obrot
		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		//Obraca lewo/prawo (yaw?)
		orientation = glm::rotate(orientation, glm::radians(-rotY), up);
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	
}

bool Camera::IsMouseOverWindow(double& x, double& y) 
{
	return (x<0 || x>width || y<0 || y>height);
}