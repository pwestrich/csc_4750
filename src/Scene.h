
#ifndef SCENE_H
#define SCENE_H

#include <vector>

class BasicObject;
class InstanceObject;
class Matrix4;

class Scene {

private:

	//keep track of all the basic and shared objects
	//the vectors will memory manage for me
	std::vector<BasicObject*> objects;
	std::vector<InstanceObject*> instances;

public:

	Scene();

	//renders every InstanceObjectgiven the windowing matrix
	void render(const Matrix4 &windowingMatrix) const;

};

#endif
