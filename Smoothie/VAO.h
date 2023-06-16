#pragma once
#include <iostream>
#include <GL/glew.h>
#include <string>
#include "VBO.h"
/*
Moje VAO
*/
class VAO
{
public:
	// ID reference for the Vertex Array Object
	unsigned int ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO to the VAO using a certain layout
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};