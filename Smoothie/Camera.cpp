#include "Camera.h"

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

void Camera::HandleInput()
{
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
	{
		position += speed * orientation;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position += speed * -orientation;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		position += speed * up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		position += speed * -up;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		double mouseX { (double)sf::Mouse::getPosition(window).x };
		double mouseY { (double)sf::Mouse::getPosition(window).y };

		if (IsMouseOverWindow(mouseX, mouseY)) return;

		float rotX{ sensitivity * (float)(mouseY - (height / 2)) / height };
		float rotY{sensitivity * (float)(mouseX - (width / 2)) / width};

		//Obraca gora/dol
		glm::vec3 newOrientation {glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up))) };

		// Ogranicza obrot
		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		//Obraca lewo/prawo
		orientation = glm::rotate(orientation, glm::radians(-rotY), up);
	}
	*/
}

bool Camera::IsMouseOverWindow(double& x, double& y) 
{
	return (x<0 || x>width || y<0 || y>height);
}