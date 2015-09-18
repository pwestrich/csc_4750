
#include "Scene.h"
#include "SceneNode.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

Scene::Scene(){

	//the root scene node has no parent
	rootSceneNode = new SceneNode(NULL);

	//make pointers for each instance and basic object
	BasicObject *obj = new BasicObject("sphere.txt");
	objects.push_back(obj);

	//replace the filename with a different one if you want
	InstanceObject *inst1 = new InstanceObject(obj, "trs1.txt");
	InstanceObject *inst2 = new InstanceObject(obj, "trs2.txt");

	instances.push_back(inst1);
	instances.push_back(inst2);

	//create scene nodes for the objects with th root as the parent
	SceneNode *node1 = new SceneNode(rootSceneNode);
	SceneNode *node2 = new SceneNode(rootSceneNode);

	rootSceneNode->addChildNode(node1);
	rootSceneNode->addChildNode(node2);

	node1->addChildObject(inst1);
	node2->addChildObject(inst2);

	nodes.push_back(node1);
	nodes.push_back(node2);

}

Scene::~Scene(){

	delete rootSceneNode;

}

//renders every InstanceObjectgiven the windowing matrix
void Scene::render(const Matrix4 &windowingMatrix) const {

	rootSceneNode->render(windowingMatrix);

}
