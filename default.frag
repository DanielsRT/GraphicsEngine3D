#version 330 core
// Output colors in RGBA
out vec4 FragColor;

// Import color from vertex shader
in vec3 color;
// Import texture coordinates from vertex shader
in vec2 texCoord;
// Import the normal from vertex shader
in vec3 Normal;
// Import current object position from vertex shader
in vec3 crntPos;

// Get texture units from main
uniform sampler2D tex0;
uniform sampler2D tex1;
// Get color of the light from main
uniform vec4 lightColor;
// Get position of the light object from main
uniform vec3 lightPos;
// Get camera position from main
uniform vec3 camPos;

void main()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// output final color
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient) + texture(tex1, texCoord).r * specular;
}