#include"Model.h"

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 800;


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

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
   
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Create camera object
    Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

    Model model("models/bunny/scene.gltf");

    while (!glfwWindowShouldClose(window))
    {
        // Set background color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Control camera inputs
        camera.Inputs(window);
        // Send camera matrix to the vertex shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        model.Draw(shaderProgram, camera);

        // Swap back buffer with front buffer
        glfwSwapBuffers(window);
        // handles GLFW events during execution
        glfwPollEvents();
    }

    // Delete shader and vertex objects
    shaderProgram.Delete();
    // Delete window
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}