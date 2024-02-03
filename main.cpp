#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// vertices coordinates
GLfloat vertices[] =
{//             Coordinates                       //        Colors
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,        0.8f, 0.3f, 0.02f,// Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,         1.0f, 0.4f, 0.32f,// Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,      0.8f, 0.5f, 0.17f,// Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,     0.7f, 0.3f, 0.02f,// Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,      0.3f, 0.7f, 0.25f,// Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,         0.6f, 0.9f, 0.7f,// Inner down
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

    // Create Shader object
    Shader shaderProgram("default.vert", "default.frag");

    // Create and bind vertex array object
    VAO VAO1;
    VAO1.Bind();

    //Create buffer objects
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Link VBO attributes and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
    // Unbind objects to prevent modification
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Get ID of uniform variable 'scale'
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Select shader program
        shaderProgram.Activate();
        // Assign 'scale' value. Always do after shader program activation.
        glUniform1f(uniID, 0.5f);
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