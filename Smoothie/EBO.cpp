#include "EBO.h"
/*
Element Buffer Object
An EBO is a buffer, just like a vertex buffer object, that stores indices that OpenGL uses to decide what vertices to draw. 
This so called indexed drawing is exactly the solution to our problem.
*/
EBO::EBO(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);//1 bo mamy jeden obiekt i paczka vertow tego obiektu
	UpdateBufferData(indices);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void EBO::UpdateBufferData(std::vector<GLuint>& indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);//wybieramy ten bufor jako aktywny (maszyna stanow!)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);//przesylamy dane
}
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}