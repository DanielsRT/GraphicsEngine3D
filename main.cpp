#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);\n"
"}\n\0";

static GLuint CreateShader()
{
    // Create vertex Shader object
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach vertex shader source code to object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile vertex shader to machine code
    glCompileShader(vertexShader);

    // Create fragment shader object
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach fragment shader source code to object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile fragment shader to machine code
    glCompileShader(fragmentShader);

    // Create shader program object
    GLuint shaderProgram = glCreateProgram();

    // Attach vertex and fragment shaders to program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link shaders with program
    glLinkProgram(shaderProgram);

    // Delete shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

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

    // Create shader program
    GLuint shaderProgram = CreateShader();

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