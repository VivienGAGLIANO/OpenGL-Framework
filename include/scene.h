#ifndef SCENE_H
#define SCENE_H

#include <vector>


class Scene
{
public:
	Scene();
	render(Renderer& engine);

private:
	Light light;
	Camera camera;
	vector<Object> objects;
};

#endif