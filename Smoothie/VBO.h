#pragma once
#include <iostream>
#include <GL/glew.h>
#include <glm.hpp>
#include <vector>
/*
Klasa odpowiada za Vertex Buffer
https://www.khronos.org/opengl/wiki/Vertex_Specification
*/
struct Vertex 
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};
class VBO
{
public:
	unsigned int ID;
	VBO(std::vector <Vertex>& vertices);
	void Bind();
	void Unbind();
	void Delete();
	void UpdateBufferData(std::vector <Vertex>& vertices);
};