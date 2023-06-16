#include "MeshRenderer.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
{
	mesh = new Mesh(vertices, indices, textures);
	SetShader(nullptr);
}

MeshRenderer::MeshRenderer(Shader* shader)
{
	mesh = new Mesh(vertices, indices, textures);
	SetShader(shader);
}

MeshRenderer::~MeshRenderer()
{
	delete mesh;
}

void MeshRenderer::DrawMesh(Camera& camera)
{
	mesh->Draw(*objectShader, camera);
}

void MeshRenderer::SetShader(Shader* shader)
{
	/*
	Moze warto dodac instancjonowanie shaderow
	Ulatwi to zmiane pozycji
	*/
	objectShader = shader;
	if (objectShader == nullptr) return;
	objectShader->Activate();

	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, position);
	glUniformMatrix4fv(glGetUniformLocation(objectShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
}

void MeshRenderer::UpdateVertexPosition()
{
	mesh->UpdateVert(0);
}