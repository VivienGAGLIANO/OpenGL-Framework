#ifndef MODEL_H
#define MODEL_H


class Model
{
public:
	Model();


private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
};

#endif