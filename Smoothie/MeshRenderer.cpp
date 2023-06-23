#include "MeshRenderer.h"
#include "Mesh.h"


MeshRenderer::MeshRenderer()
{
	mesh = new Mesh();
	SetShader(nullptr);
}
MeshRenderer::MeshRenderer(Shader* shader)
{
	mesh = new Mesh();
	SetShader(shader);
}
MeshRenderer::~MeshRenderer()
{
	delete mesh;
}

void MeshRenderer::AddVertex(Vertex v, int* indices, int inLen, bool refresh)
{
	mesh->PutNewVert(v);
	for (int i{ 0 }; i < inLen; i++) 
	{
		int newInd = *indices+i;
		mesh->PutNewIndices(newInd);
	}
	if (refresh) 
	{
		mesh->UpdateMesh();
	}
}

void MeshRenderer::LoadMeshFromFile(const char* fileName)
{
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		std::cout << "Cant open file! " << fileName << std::endl;
		return;
	}
	else 
	{
		std::cout << "Opened file " << fileName << std::endl;
	}
	std::string line;
	while (getline(input, line))
	{
		//std::cout << line << std::endl;
		std::vector<float> parameters {Explode(line, ',')};
		glm::vec3 coords{ 0,0,0 };
		glm::vec3 colors{ 0,0,0 };
		glm::vec3 normals{ 0,0,0 };
		glm::vec2 texCoords{ 0,0,};
		
		int indLen = parameters.size() - 11;
		if (indLen < 1)indLen = 1;
		int* ind = new int[indLen];
		ind[0] = 0;
		if (parameters.size() >= 3) 
		{
			coords.x = parameters[0];
			coords.y = parameters[1];
			coords.z = parameters[2];
		}
		if (parameters.size() >= 6)
		{
			colors.x = parameters[3];
			colors.y = parameters[4];
			colors.z = parameters[5];
		}
		if (parameters.size() >= 9)
		{
			normals.x = parameters[6];
			normals.y = parameters[7];
			normals.z = parameters[8];
		}
		if (parameters.size() >= 11)
		{
			texCoords.x = parameters[9];
			texCoords.y = parameters[10];
		}
		if (parameters.size() > 12)
		{
			for (int i = 0; i < indLen; i++) 
			{
				ind[i] = (int)parameters[i+11];
			}
		}
		Vertex nv = Vertex{ coords, colors, normals, texCoords };
		AddVertex(nv, ind, indLen);
	}
	input.close();
	mesh->UpdateMesh();
}

void MeshRenderer::SaveMeshToFile(const char* fileName)
{
	std::cout << "Not yet implemented!" << fileName << std::endl;
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

void MeshRenderer::UpdateVertexPosition(int id, glm::vec3 moveVec)
{
	mesh->UpdateVert(id, moveVec);
}

glm::vec3 MeshRenderer::GetMeshVertPosition(int id)
{
	return mesh->GetVertPos(id);
}

int MeshRenderer::MeshVericiesCount() 
{
	return mesh->VericiesInMeshCount();
}

std::vector<float> MeshRenderer::Explode(std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<float> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(std::stof(buff)); buff = ""; }
	}
	if (buff != "") v.push_back(std::stof(buff));

	return v;
}