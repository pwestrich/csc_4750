
#include "Scene.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

Scene::Scene(){

	//make shared pointers for each instance and basic object
	std::shared_ptr<BasicObject> obj = std::make_shared<BasicObject>("sphere.txt");
	objects.push_back(obj);

	//let's try to make a different sphere.
	Matrix4 translate = createTranslateMatrix(1.0, 0.2, 1.0);
	Matrix4 rotateX = createRotationMatrixX(45.0);
	Matrix4 rotateY = createRotationMatrixY(10.0);
	Matrix4 rotateZ = createRotationMatrixZ(0.0);
	Matrix4 scale = createScaleMatrix(-0.3, 0.3, 0.0);

	//replace the filename with a different one if you want
	std::shared_ptr<InstanceObject> inst1 = std::make_shared<InstanceObject>(obj, "trs1.txt");
	std::shared_ptr<InstanceObject> inst2 = std::make_shared<InstanceObject>(obj, "trs2.txt");

	instances.push_back(inst1);
	instances.push_back(inst2);

}

//renders every InstanceObjectgiven the windowing matrix
void Scene::render(const Matrix4 &windowingMatrix) const {

	for (size_t i = 0; i < instances.size(); ++i){

		instances[i]->render(windowingMatrix);

	}

}
