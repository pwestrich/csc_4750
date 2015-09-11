
#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class BasicObject;
class InstanceObject;

class Scene {

private:

	std::vector<std::shared_ptr<BasicObject>> objects;
	std::vector<std::shared_ptr<InstanceObject>> instances;

public:

	Scene();
	~Scene();

	//renders every InstanceObject
	void render();

};

#endif
