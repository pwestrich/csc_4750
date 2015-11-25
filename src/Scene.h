
#ifndef SCENE_H
#define SCENE_H

#include <vector>

class BasicObject;
class InstanceObject;
class SceneNode;

class Scene {

private:

	//keep track of all the basic and shared objects
	//the vectors will memory manage for me
	std::vector<SceneNode*> nodes;
	std::vector<BasicObject*> objects;
	std::vector<InstanceObject*> instances;

	float attenuation;

	//the root scene node
	SceneNode *rootSceneNode;

public:

	Scene();
	~Scene();

	//renders every InstanceObjectgiven the windowing matrix
	void render() const;

};

#endif
