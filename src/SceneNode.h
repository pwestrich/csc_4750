
#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <vector>

#include "Matrix4.h"

class InstanceObject;

class SceneNode {

private:

	//the parent scene node of this object
	const SceneNode *parent;

	//this object's children
	std::vector<SceneNode*> children;

	//any InstanceObjects attached to this item
	std::vector<InstanceObject*> objects;

	//this node's transform
	Matrix4 transform;

public:

	//create a new SceneNode with an optional transform
	SceneNode(const SceneNode *newParent, const Matrix4 &newTransform = Matrix4::identity()) : parent(newParent), transform(newTransform){}

	//build up transforms
	void buildTransform(const Matrix4 &newTransform);

	//renders every child
	void render(const Matrix4 &newTransform) const;

	//add a new child node
	void addChildNode(SceneNode *newNode);

	//add a new child object
	void addChildObject(InstanceObject *newObject);

};

#endif
