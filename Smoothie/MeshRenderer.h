#pragma once
#include "Transform.h"
#include "Mesh.h"

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
private:
    Mesh* mesh;
    Shader* objectShader;

private:
    std::vector <Vertex> vertices
    { //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
        Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(2.0f, 0.5f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
    };

    std::vector <GLuint> indices
    {
        0, 1, 2,
        0, 2, 3,
        2, 3, 4
    };

    std::vector <Texture> textures
    {
        Texture("Textures/planks.png","diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("Textures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };
};