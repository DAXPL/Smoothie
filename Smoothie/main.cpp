//https://www.youtube.com/watch?v=ukDmQl9Cz6c
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Mesh.h"
#include "MeshRenderer.h"
#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat4x4.hpp> // glm::mat4
#include <gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

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

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
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

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    glEnable(GL_DEPTH_TEST);
    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    Shader shaderProgram("Shaders/Basic.shader");
    MeshRenderer testowyModel(&shaderProgram);
    GLLogCall(0);

    std::cout << "Global lighting" << std::endl;
    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), 1, 1, 1, 1);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), 0, 0, 0);
    GLLogCall(0);

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 1.0f);

    bool running = true;
    unsigned long frame{ 0 };
    GLLogCall(0);
    std::cout << "Game loop started!" << std::endl;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        camera.HandleInput();

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
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return EXIT_SUCCESS;
}

