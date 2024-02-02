#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    // Read source code files
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

    // Convert strings to char arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

    // Create vertex Shader object
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach vertex shader source code to object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile vertex shader to machine code
    glCompileShader(vertexShader);

    // Create fragment shader object
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach fragment shader source code to object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile fragment shader to machine code
    glCompileShader(fragmentShader);

    // Create shader program object
    ID = glCreateProgram();

    // Attach vertex and fragment shaders to program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Link shaders with program
    glLinkProgram(ID);

    // Delete shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}