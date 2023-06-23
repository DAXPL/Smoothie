#pragma once
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <vector>
/*
Element Buffer Object
An EBO is a buffer, just like a vertex buffer object, that stores indices that OpenGL uses to decide what vertices to draw.
*/
class EBO
{
public:
	unsigned int ID;
	EBO(std::vector<GLuint>& indices);
	void UpdateBufferData(std::vector<GLuint>& indices);
	void Bind();
	void Unbind();
	void Delete();
};