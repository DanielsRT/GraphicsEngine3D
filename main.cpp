#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// vertices coordinates
GLfloat vertices[] =
{
    -0.6f, -0.6f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.6f, -0.6f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.6f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
    - 0.6f / 2, 0.6f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.6f / 2, 0.6f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.6f * float(sqrt(3)) / 3, 0.0f // Inner down
};
// Indices for vertex order
GLuint indices[] =
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

int main()
{
    // Initialize GLFW
    glfwInit();

    // Specify the version of OpenGL in use (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Have GLFW use the CORE profile from OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a 800x800 GLFWwindow
    GLFWwindow* window = glfwCreateWindow(800, 800, "3D Graphics", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Add window to the current context
    glfwMakeContextCurrent(window);

    // Load GLAD, which will configure OpenGL
    gladLoadGL();

    // Specify view coordinates and size. (x=0, y=0, 800x800)
    glViewport(0, 0, 800, 800);

    
    Shader shaderProgram("default.vert", "default.frag");


    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Select shader program
        shaderProgram.Activate();
        // Bind VAO so OpenGL can use it
        VAO1.Bind();
        // Draw the triangle using the 'GL_TRIANGLES' type
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        // handles GLFW events during execution
        glfwPollEvents();
    }

    // Delete shader and vertex objects
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    // Delete window
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}