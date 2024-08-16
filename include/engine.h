#ifndef RENDERER_H
#define RENDERER_H

#include <glfw3.h>

#include "object.h"
#include "scene.h"
#include "skybox.h"


class Engine
{
public:
	~Engine();
	Engine();

	void render_skybox(const Skybox& skybox) const;
	void render(const Scene& scene) const;
	void draw_ui(bool ui_active);
	void render_ui();
};

#endif