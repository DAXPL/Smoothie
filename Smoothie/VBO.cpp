#include "VBO.h"

VBO::VBO(std::vector <Vertex>& vertices)
{
	glGenBuffers(1, &ID);//1 bo mamy jeden obiekt i paczka vertow tego obiektu
	UpdateBufferData(vertices);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void VBO::UpdateBufferData(std::vector <Vertex>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);//wybieramy ten bufor jako aktywny (maszyna stanow!)
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);//przesylamy dane
}