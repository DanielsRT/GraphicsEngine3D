#version 330 core

// object coordinates
layout (location = 0) in vec3 aPos;
// normals (not always normalized)
layout (location = 1) in vec3 aNormal;
// colors
layout (location = 2) in vec3 aColor;
// texture coordinates
layout (location = 3) in vec2 aTex;


// output current position to the fragment shader
out vec3 crntPos;
// output the normal to the fragment shader
out vec3 Normal;
// output color to the fragment shader
out vec3 color;
// output texture coordinates to fragment shader
out vec2 texCoord;


// import camera matrix from main
uniform mat4 camMatrix;
// import model matrix from main
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
	// calculate current position
	crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
	// assign the normal from vertex data
	Normal = aNormal;
	// assign colors from vertex data
	color = aColor;
	// assign texture coordinates from vertex data
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;

	// output coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}