#ifndef APPLICATION_H
#define APPLICATION_H

#include "scene.h"


class Application
{
public:
	Application();
	void start();

private:
	void init();
	void terminate();
	void update_camera(Camera &camera);

	Renderer *engine;
	Scene *scene;
};

#endif