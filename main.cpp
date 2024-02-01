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

    // vertices coordinates
    GLfloat vertices[] =
    {
        -0.6f, -0.6f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.6f, -0.6f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.6f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
    };

    // Create containers for vertex array and vertex buffer
    GLuint VAO, VBO;

    // Generate vertex array and buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Make VAO the current vertex array
    glBindVertexArray(VAO);

    // Bind VBO as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Add the vertices into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the vertex attribute so OpenGL can read the vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable the vertex attribute
    glEnableVertexAttribArray(0);

    // Bind VAO and VBO to 0 so they can't be mistakenly modified
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Set background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // Clear back buffor and assign the new color
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap back and front buffer
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Select shader program
        glUseProgram(shaderProgram);
        // Bind VAO so OpenGL can use it
        glBindVertexArray(VAO);
        // Draw the triangle using the 'GL_TRIANGLES' type
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        // handles GLFW events during execution
        glfwPollEvents();
    }

    // Delete shader and vertex objects
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Delete window
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}