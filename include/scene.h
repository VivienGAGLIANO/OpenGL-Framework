#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "object.h"
#include "renderer.h"

struct Light {};
struct Camera {};


class Scene
{
public:
	Scene();
	void render(Renderer& engine);

private:
	Light light;
	Camera camera;
	std::vector<Object> objects;
};

#endif