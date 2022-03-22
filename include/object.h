#ifndef OBJECT_H
#define OBJECT_H


class Object
{
public:
	Object();

private:
	glm::mat4 model_matrix;
	Material material;
	Model model;
};

#endif