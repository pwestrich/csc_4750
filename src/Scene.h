
#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Light.h"

class BasicObject;
class InstanceObject;
class SceneNode;
class Matrix4;

class Scene {

private:

	//keep track of all the basic and shared objects
	//the vectors will memory manage for me
	std::vector<SceneNode*> nodes;
	std::vector<BasicObject*> objects;
	std::vector<InstanceObject*> instances;

	//the lights of the scene
	Light point;
	Light ambient;

	float attenuation;
	float shininess;

	//the root scene node
	SceneNode *rootSceneNode;

	void readLights(const std::string &filename);

public:

	Scene();
	~Scene();

	//renders every InstanceObjectgiven the windowing matrix
	void render(const Matrix4 &windowingMatrix) const;

};

#endif
