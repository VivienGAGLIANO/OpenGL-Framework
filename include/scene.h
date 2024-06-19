#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "camera.h"
#include "light.h"
#include "object.h"


class Scene
{
public:
	Scene();
	~Scene();
	std::shared_ptr<Camera> get_camera() const;
	std::shared_ptr<Light> get_light() const;
	void update(const double& delta_time);

	static std::shared_ptr<Scene> active_scene;
	std::vector<std::shared_ptr<Object>> objects;

private:
	void populate();

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Light> light;
};

#endif