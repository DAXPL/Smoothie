#pragma once
#include <iostream>
#include <GL/glew.h>
#include <string>
#include "VBO.h"

class VAO
{
public:
	unsigned int ID;
	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};