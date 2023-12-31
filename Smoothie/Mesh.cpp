#include "Mesh.h"

Mesh::Mesh() 
{
    verticies = {};
    indicies = {};
    textures = 
    {
        Texture("Textures/planks.png","diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("Textures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };
    vao = new VAO();
    vbo = new VBO(verticies);
    ebo = new EBO(indicies);
}

Mesh::Mesh(std::vector <Vertex>& _verticies, std::vector <GLuint>& _indicies, std::vector <Texture>& _textures) 
{
	verticies = _verticies;
	indicies = _indicies;
	textures = _textures;
    vao = new VAO();
    vbo = new VBO(verticies);
    ebo = new EBO(indicies);
    UpdateMesh();
}

Mesh::~Mesh()
{
    vao->Delete();
    vbo->Delete();
    ebo->Delete();

    for (int i = 0; i < textures.size(); i++) 
    {
        textures[i].Delete();
    }

    delete vao;
    delete ebo;
    delete vbo;
}

void Mesh::PutNewVert(Vertex v)
{
    verticies.push_back(v);
}

void Mesh::PutNewIndices(int i)
{
    indicies.push_back(i);
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
    if (vao == nullptr || vbo==nullptr || ebo==nullptr) return;
    shader.Activate();
    vao->Bind();
    unsigned int numDiffuse{ 0 };
    unsigned int numSpecular{ 0 };

    for (unsigned int i{ 0 }; i < textures.size(); i++) 
    {
        std::string num{""};
        std::string type{ textures[i].type };
        if (type == "diffuse") 
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        else 
        {
            std::cout << "Wrong texture type!" << std::endl;
        }
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
    camera.Matrix(shader, "camMatrix");
    glDrawElements(GL_TRIANGLES,indicies.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::UpdateMesh()
{
    if (vao == nullptr || vbo == nullptr || ebo == nullptr)return;
    vao->Bind();
    vbo->Bind();
    ebo->Bind();

    vbo->UpdateBufferData(verticies);
    ebo->UpdateBufferData(indicies);

    vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao->LinkAttrib(*vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao->LinkAttrib(*vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

    //odpinam bufory zeby ich przypadkiem nie zmienic
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();//to zawsze na koniec
}

void Mesh::UpdateVert(int id, glm::vec3 moveVec)
{
    if (id >= verticies.size()) return;

    verticies.at(id).position = moveVec;
    vbo->UpdateBufferData(verticies);
}

glm::vec3 Mesh::GetVertPos(int id) 
{
    if (id >= verticies.size()) return glm::vec3(0, 0, 0);
    return verticies.at(id).position;
}

int Mesh::VericiesInMeshCount() 
{
    return verticies.size();
}