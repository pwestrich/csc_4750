
#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class BasicObject;
class InstanceObject;
class Matrix4;

class Scene {

private:

	//keep track of all the basic and shared objects
	std::vector<std::shared_ptr<BasicObject>> objects;
	std::vector<std::shared_ptr<InstanceObject>> instances;

public:

	Scene();

	//renders every InstanceObjectgiven the windowing matrix
	void render(const Matrix4 &windowingMatrix) const;

};

#endif
