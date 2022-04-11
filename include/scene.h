#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "camera.h"
#include "engine.h"
#include "object.h"

struct Light{};
// struct Camera{};

class Engine;

class Scene
{
public:
	~Scene();
	Camera* get_camera() const;
	void update(const double& delta_time);
	void updateVelocity(const double& delta_time);
	void updatePosition(const double& delta_time);
	void render(Engine* engine);
	static Scene* get_instance();

private:
	Scene();
	void populate();

	static Scene *instance;
	// Light light;
	Camera* camera;
	std::vector<Object*> objects;
};

#endif