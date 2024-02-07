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
#include"Camera.h"

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 800;

// vertices coordinates
GLfloat vertices[] =
{//      Coordinates      //       Colors        //  TexCoord
    -0.5f,  0.0f,  0.5f,      0.8f, 0.8f, 0.52f,    0.0f, 0.0f, 
    -0.5f,  0.0f, -0.5f,      1.0f, 0.2f, 0.32f,    5.0f, 0.0f, 
     0.5f,  0.0f, -0.5f,      0.8f, 0.9f, 0.17f,    0.0f, 0.0f, 
     0.5f,  0.0f,  0.5f,      0.7f, 0.7f, 0.02f,    5.0f, 0.0f, 
     0.0f,  0.8f,  0.0f,      0.7f, 0.7f, 0.32f,    2.5f, 5.0f 
};
// Indices for vertex order
GLuint indices[] =
{
    0, 2, 1,  
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
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
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "3D Graphics", NULL, NULL);
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
    glViewport(0, 0, windowWidth, windowHeight);

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

    // Texture
    Texture brickTexture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    brickTexture.texUnit(shaderProgram, "tex0", 0);
   
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Create camera object
    Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        // Set background color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Select shader program
        shaderProgram.Activate();

        // Send camera matrix to the vertex shader
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        
        // Bind the texture so it renders
        brickTexture.Bind();
        // Bind VAO so OpenGL can use it
        VAO1.Bind();
        // Draw the triangle using the 'GL_TRIANGLES' type
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        // handles GLFW events during execution
        glfwPollEvents();
    }

    // Delete shader and vertex objects
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    brickTexture.Delete();
    shaderProgram.Delete();
    // Delete window
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}