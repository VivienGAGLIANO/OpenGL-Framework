#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "camera.h"
#include "engine.h"
#include "object.h"

inline bool cartoon = false ;


struct Light
{
	glm::vec3 position;

	glm::vec3 ambiant;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float shininess;

	inline void set_position(const glm::vec3& p) { position = p; }
};


class Engine;

class Scene
{
public:
	~Scene();
	Camera* get_camera() const;
	Light* get_light() const;
	void update(const double& delta_time);
	void updateVelocity(const double& delta_time);
	void updatePosition(const double& delta_time);
	void resetForces();
	void render(Engine* engine);
	static Scene* get_instance();

private:
	Scene();
	void populate();
	void populateCartoon();

	static Scene *instance;
	Camera* camera;
	Light* light;
	std::vector<Object*> objects;
};

#endif