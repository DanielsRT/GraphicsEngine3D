#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;

class Model
{
public:
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera);

private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;
};
#endif