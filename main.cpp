#include"Mesh.h"

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 800;

// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
    Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};
// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
    Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
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

    Texture textures[]
    {
        Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    // Create Shader object
    Shader shaderProgram("default.vert", "default.frag");
    // Store mesh data in vectors for the mesh
    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh floor(verts, ind, tex);

    // Shader for light cube
    Shader lightShader("light.vert", "light.frag");
    // Store mesh data in vectors for the light mesh
    std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, tex);

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    

   
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Create camera object
    Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        // Set background color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Control camera inputs
        camera.Inputs(window);
        // Send camera matrix to the vertex shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // Draw the meshes
        floor.Draw(shaderProgram, camera);
        light.Draw(lightShader, camera);

        // Swap back buffer with front buffer
        glfwSwapBuffers(window);
        // handles GLFW events during execution
        glfwPollEvents();
    }

    // Delete shader and vertex objects
    shaderProgram.Delete();
    lightShader.Delete();
    // Delete window
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}