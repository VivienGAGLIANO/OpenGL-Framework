#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "object.h"
#include "engine.h"

struct Light{};
struct Camera{};

class Engine;

class Scene
{
public:
	Scene();
	void update(const double& delta_time);
	void render(Engine* engine);

private:
	Light light;
	Camera camera;
	std::vector<Object> objects;
};

#endif