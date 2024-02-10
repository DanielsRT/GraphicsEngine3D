#version 330 core

// object coordinates
layout (location = 0) in vec3 aPos;
// colors
layout (location = 1) in vec3 aColor;
// texture coordinates
layout (location = 2) in vec2 aTex;
// normals (not always normalized)
layout (location = 3) in vec3 aNormal;

// output color to the fragment shader
out vec3 color;
// output texture coordinates to fragment shader
out vec2 texCoord;
// output the normal to the fragment shader
out vec3 Normal;
// output current position to the fragment shader
out vec3 crntPos;

// import camera matrix from main
uniform mat4 camMatrix;
// import model matrix from main
uniform mat4 model;

void main()
{
	// calculate current position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// output coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);

	// assign colors from vertex data
	color = aColor;
	// assign texture coordinates from vertex data
	texCoord = aTex;
	// assign the normal from vertex data
	Normal = aNormal;
}