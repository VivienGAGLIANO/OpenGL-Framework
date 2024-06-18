#ifndef LIGHT_H
#define LIGHT_H


struct Light
{
	glm::vec3 position;

	glm::vec3 ambiant;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float shininess;

	inline void set_position(const glm::vec3& p) { position = p; }
};


#endif // LIGHT_H