#pragma once
#include "Transform.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class MeshRenderer: public Transform
{
public:
    MeshRenderer();
    MeshRenderer(Shader* _shader);
    ~MeshRenderer();

    void DrawMesh(Camera& camera);
    void SetShader(Shader* _shader);

    void UpdateVertexPosition(int id, glm::vec3 moveVec);
    glm::vec3 GetMeshVertPosition(int id);
    int MeshVericiesCount();
    void LoadMeshFromFile(const char* fileName);
    void SaveMeshToFile(const char* fileName);
    void AddVertex(Vertex v, int* indices, int inLen, bool refresh=false);
private:
    Mesh* mesh;
    Shader* objectShader;
    std::vector<float> Explode(std::string& s, const char& c);
};