#pragma once
#include <glm.hpp>
class Transform 
{
	public:
		Transform();
		void Move(glm::vec3 moveVec);
		void Move(float x, float y, float z);
		glm::vec3 position;
		glm::vec3 orientation;
		glm::vec3 up;

};