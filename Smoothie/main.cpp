//https://www.youtube.com/watch?v=ukDmQl9Cz6c
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

int main()
{
    std::cout << "Smoothie 0.1" << std::endl;
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Smoothie", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

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
    glViewport(0, 0, screenWidth, screenHeight);

    std::cout << "Loading shaders and meshes" << std::endl;
    Shader shaderProgram("Shaders/Basic.shader");
    MeshRenderer testowyModel(&shaderProgram);
    GLLogCall(0);

    std::cout << "Calculating global lighting" << std::endl;
    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), 1, 1, 1, 1);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), 0, 0, 0);
    GLLogCall(0);

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 20.0f);

    bool running = true;
    unsigned long frame{ 0 };
    GLLogCall(0);
    std::cout << "Main loop started!" << std::endl;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        //User input
        glfwPollEvents();
        camera.HandleInput(window);

        //Drawing
        glClearColor(0.82f, 0.82f, 0.82f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        testowyModel.UpdateVertexPosition();
        testowyModel.DrawMesh(camera);


        // Swap the screen buffers
        glfwSwapBuffers(window);

        GLLogCall(frame);
        frame++;
    }

    shaderProgram.Delete();
    glfwTerminate();
    std::cout << "Smoothie 0.1" << std::endl;
    return EXIT_SUCCESS;
}