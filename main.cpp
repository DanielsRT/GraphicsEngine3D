#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

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

    // Set background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // Clear back buffor and assign the new color
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap back and front buffer
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        // handles GLFW events during execution
        glfwPollEvents();
    }

    // Delete window
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}