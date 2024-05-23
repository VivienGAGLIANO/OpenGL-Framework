#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "scene.h"


class Application
{
public:
	Application();
	~Application();
	void start();

private:
	void initialize();
	void terminate();
	void update_camera(Camera &camera);

	std::unique_ptr<Engine> engine;
	std::shared_ptr<Scene> scene;
};

#endif