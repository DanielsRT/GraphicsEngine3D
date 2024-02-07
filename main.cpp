#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// vertices coordinates
GLfloat vertices[] =
{//      Coordinates      //        Colors
    -0.5f, -0.5f, 0.0f,      0.8f, 0.3f, 0.02f,  0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,      1.0f, 0.4f, 0.32f,  0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,      0.8f, 0.5f, 0.17f,  1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,      0.7f, 0.3f, 0.02f,  1.0f, 0.0f // Lower right corner
};
// Indices for vertex order
GLuint indices[] =
{
    0, 2, 1,  // Upper triangle
    0, 3, 2   // Lower triangle
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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind objects to prevent modification
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Get ID of uniform variable 'scale'
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Texture
    Texture coolTurtle("turtle_sunglasses.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    coolTurtle.texUnit(shaderProgram, "tex0", 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Select shader program
        shaderProgram.Activate();
        // Assign 'scale' value. Always do after shader program activation.
        glUniform1f(uniID, 0.5f);
        // Bind the texture so it renders
        coolTurtle.Bind();
        // Bind VAO so OpenGL can use it
        VAO1.Bind();
        // Draw the triangle using the 'GL_TRIANGLES' type
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        // handles GLFW events during execution
        glfwPollEvents();
    }

    // Delete shader and vertex objects
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    coolTurtle.Delete();
    shaderProgram.Delete();
    // Delete window
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}