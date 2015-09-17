
#include "Scene.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

Scene::Scene(){

	//make shared pointers for each instance and basic object
	std::shared_ptr<BasicObject> obj = std::make_shared<BasicObject>("sphere.txt");
	//std::shared_ptr<InstanceObject> inst = std::make_shared<InstanceObject>(obj);

	objects.push_back(obj);
	//instances.push_back(inst);

	//let's try to make a different sphere.
	Matrix4 translate = createTranslateMatrix(1.0, 0.2, 1.0);
	Matrix4 rotateX = createRotationMatrixX(45.0);
	Matrix4 rotateY = createRotationMatrixY(10.0);
	Matrix4 rotateZ = createRotationMatrixZ(0.0);
	Matrix4 scale = createScaleMatrix(-0.3, 0.3, 0.0);

	std::shared_ptr<InstanceObject> inst2 = std::make_shared<InstanceObject>(obj);

	inst2->buildTransform(translate);
	inst2->buildTransform(rotateX);
	inst2->buildTransform(rotateY);
	inst2->buildTransform(rotateZ);
	inst2->buildTransform(scale);

	instances.push_back(inst2);

}

//renders every InstanceObjectgiven the windowing matrix
void Scene::render(const Matrix4 &windowingMatrix) const {

	for (size_t i = 0; i < instances.size(); ++i){

		instances[i]->render(windowingMatrix);

	}

}
