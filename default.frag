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

vec4 pointLight()
{
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);


	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}

void main()
{
	// output final color
	FragColor = pointLight();
}