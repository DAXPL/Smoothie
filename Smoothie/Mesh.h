#pragma once
#include <string>
#include <vector>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"
#include "Transform.h"

class Mesh 
{
	std::vector <Vertex> verticies;
	std::vector <GLuint> indicies;
	std::vector <Texture> textures;

	VAO* vao;
	VBO* vbo;
	EBO* ebo;
public:
	Mesh();
	Mesh(std::vector <Vertex>& _verticies, std::vector <GLuint>& _indicies, std::vector <Texture>& _textures);
	~Mesh();
	void UpdateMesh();
	void Draw(Shader& shader, Camera& camera);
	void UpdateVert(int id, glm::vec3 moveVec);
	glm::vec3 GetVertPos(int id);
};