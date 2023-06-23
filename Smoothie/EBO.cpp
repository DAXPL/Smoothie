#include "EBO.h"

EBO::EBO(std::vector<GLuint>& indices)
{
	//1 poniewa¿ mamy jeden obiekt + paczka vertow tego obiektu
	glGenBuffers(1, &ID);
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