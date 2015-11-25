
#include <cassert>
#include <vector>

#include "SceneNode.h"
#include "InstanceObject.h"

//build up transforms
void SceneNode::buildTransform(const Matrix4 &newTransform){

	transform = newTransform * transform;

}

//renders every child
void SceneNode::render(const Matrix4 &newTransform) const {

	//apply this node's instance transform to every child
	Matrix4 current = newTransform * transform;

	for (size_t i = 0; i < objects.size(); ++i){

		objects[i]->render(current);

	}

	for (size_t i = 0; i < children.size(); ++i){

		children[i]->render(current);

	}

}

//add a new child node
void SceneNode::addChildNode(SceneNode *newNode){

	assert(newNode);

	children.push_back(newNode);

}

//add a new child object
void SceneNode::addChildObject(InstanceObject *newObject){

	assert(newObject);

	objects.push_back(newObject);

}
