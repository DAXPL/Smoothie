//https://www.youtube.com/watch?v=ukDmQl9Cz6c
#include <cstdlib>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Mesh.h"
#include "MeshRenderer.h"
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

const GLint WIDTH = 800, HEIGHT = 600;

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
static bool GLLogCall(unsigned long frame)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[Frame " << frame << "][OpenGL Error]" << error << std::endl;
        return false;
    }
    return true;
}
float vec3Magnitude(glm::vec3 vec) 
{
    float magnitude = vec.x + vec.y + vec.z;
    return abs(magnitude);
}
int ClampInt(int a, int min, int max) 
{
    if (a < min) a = min;
    if (a > max) a = max;
    return a;
}
void ManageUI(MeshRenderer* workMesh, int* vert)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Smoothie UI");
    ImGui::Text("Vertex manipulation");

    glm::vec3 vertPos = workMesh->GetMeshVertPosition(*vert);
    glm::vec3 inputPosition(vertPos.x, vertPos.y, vertPos.z);

    ImGui::InputInt("Select vert", vert);
    *vert = ClampInt(*vert, 0, workMesh->MeshVericiesCount() - 1);
    ImGui::InputFloat("X", &inputPosition.x);
    ImGui::InputFloat("Y", &inputPosition.y);
    ImGui::InputFloat("Z", &inputPosition.z);

    if (vec3Magnitude(inputPosition - vertPos) > 0) workMesh->UpdateVertexPosition(*vert, inputPosition);

    ImGui::End();
}
int main()
{
    std::cout << "Smoothie 0.1" << std::endl;
    glfwInit();

    //GLFW options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Smoothie", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WIDTH, HEIGHT);

    std::cout << "Loading shaders and meshes" << std::endl;
    Shader shaderProgram("Shaders/Basic.shader");
    MeshRenderer workMesh(&shaderProgram);
    workMesh.LoadMeshFromFile("BaseMesh.msh");
    //workMesh.AddVertex();

    GLLogCall(0);

    std::cout << "Calculating global lighting" << std::endl;
    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), 1, 1, 1, 1);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), 0, 0, 0);
    GLLogCall(0);

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 20.0f);

    //IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    int selectedVert{ 0 };
    unsigned long frame{ 0 };
    GLLogCall(0);
    std::cout << "Main loop started!" << std::endl;
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        //Input
        glfwPollEvents();
        
        //Clear screen
        glClearColor(0.82f, 0.82f, 0.82f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Prepare and handle UI
        ManageUI(&workMesh, &selectedVert);

        camera.HandleInput(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        workMesh.DrawMesh(camera);
        
        //Display
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        GLLogCall(frame);
        frame++;
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    shaderProgram.Delete();
    glfwTerminate();
    std::cout << "End" << std::endl;
    return EXIT_SUCCESS;
}