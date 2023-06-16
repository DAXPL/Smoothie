#pragma once
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <vector>

class EBO
{
public:
	unsigned int ID;
	EBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};