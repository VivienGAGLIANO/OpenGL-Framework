#ifndef APPLICATION_H
#define APPLICATION_H

#include "scene.h"


class Application
{
public:
	Application();
	~Application();
	void start();

private:
	void init();
	void terminate();
	void update_camera(Camera &camera);

	Engine* engine;
	Scene* scene;
};

#endif