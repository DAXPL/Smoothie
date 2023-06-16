#include "Transform.h"

Transform::Transform() 
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Transform::Move(glm::vec3 moveVec)
{
	position += moveVec;
}

void Transform::Move(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}