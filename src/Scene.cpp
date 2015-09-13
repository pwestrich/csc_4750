
#include "Scene.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"

Scene::Scene(){

	//make shared pointers for each instance and basic object
	std::shared_ptr<BasicObject> obj = std::make_shared<BasicObject>("sphere.txt");
	std::shared_ptr<InstanceObject> inst = std::make_shared<InstanceObject>(obj);

	objects.push_back(obj);
	instances.push_back(inst);

}

//renders every InstanceObjectgiven the windowing matrix
void Scene::render(const Matrix4 &windowingMatrix) const {

	for (size_t i = 0; i < instances.size(); ++i){

		instances[i]->render(windowingMatrix);

	}

}
