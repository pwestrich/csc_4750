
#include "Scene.h"
#include "SceneNode.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

Scene::Scene(){

	//the root scene node has no parent
	rootSceneNode = new SceneNode();

	//create the absic objects for the robot
	BasicObject *basicCube = new BasicObject("cube.txt");
	BasicObject *basicCylinder = new BasicObject("cylinder.txt");

	objects.push_back(basicCube);
	objects.push_back(basicCylinder);

	//now make the instance objects needed of each
	InstanceObject *upperArm = new InstanceObject(basicCube);
	InstanceObject *lowerArm = new InstanceObject(basicCube);
	InstanceObject *base = new InstanceObject(basicCylinder);

	instances.push_back(upperArm);
	instances.push_back(lowerArm);
	instances.push_back(base);

	//then the transform nodes
	SceneNode *upperArmTransform = new SceneNode();
	SceneNode *lowerArmTransform = new SceneNode();
	SceneNode *baseTransform = new SceneNode();
	SceneNode *robotArm1 = new SceneNode();
	SceneNode *robotArm2 = new SceneNode();

	nodes.push_back(robotArm1);
	nodes.push_back(robotArm2);
	nodes.push_back(baseTransform);
	nodes.push_back(lowerArmTransform);
	nodes.push_back(upperArmTransform);

	//then attatch them up
	rootSceneNode->addChildNode(robotArm1);
	rootSceneNode->addChildNode(robotArm2);

	robotArm1->addChildNode(baseTransform);
	robotArm2->addChildNode(baseTransform);

	baseTransform->addChildNode(lowerArmTransform);
	baseTransform->addChildObject(base);

	lowerArmTransform->addChildNode(upperArmTransform);
	lowerArmTransform->addChildObject(lowerArm);

	upperArmTransform->addChildObject(upperArm);

	//now make all the transforms
	//upper arm instance transform
	Matrix4 scale = createScaleMatrix(.2, 1.0, 0.2);
	upperArm->buildTransform(scale);

	//lower arm instance transform
	scale = createScaleMatrix(0.2, 2.0, 0.2);
	lowerArm->buildTransform(scale);

	//upper arm transform
	Matrix4 translate1 = createTranslateMatrix(0, 1, 0);
	Matrix4 translate2 = createTranslateMatrix(0, 2, 0);
	Matrix4 rotateZ = createRotationMatrixZ(90.0);

	upperArmTransform->buildTransform(translate1);
	upperArmTransform->buildTransform(rotateZ);
	upperArmTransform->buildTransform(translate2);

	//lower arm transform
	translate1 = createTranslateMatrix(0, 2, 0);
	translate2 = createTranslateMatrix(0, 1, 0);
	rotateZ = createRotationMatrixZ(-20.0);

	lowerArmTransform->buildTransform(translate1);
	lowerArmTransform->buildTransform(rotateZ);
	lowerArmTransform->buildTransform(translate2);

	//base transform
	translate1 = createTranslateMatrix(0, -2, 0);
	Matrix4 rotateY = createRotationMatrixY(30.0);

	baseTransform->buildTransform(rotateY);
	baseTransform->buildTransform(translate1);

	//arm 1
	translate1 = createTranslateMatrix(0, 0, -3);
	scale = createScaleMatrix(0.2, 0.2, 0.2);

	robotArm1->buildTransform(scale);
	robotArm1->buildTransform(translate1);

	//arm 2
	translate1 = createTranslateMatrix(-3.0, 0.5, 0.0);
	scale = createScaleMatrix(0.2, 0.2, 0.2);
	Matrix4 rotateX = createRotationMatrixX(45.0);

	robotArm2->buildTransform(scale);
	robotArm2->buildTransform(rotateX);
	robotArm2->buildTransform(translate1);
	robotArm2->buildTransform(scale);

}

Scene::~Scene(){

	delete rootSceneNode;

}

//renders every InstanceObjectgiven the windowing matrix
void Scene::render(const Matrix4 &windowingMatrix) const {

	rootSceneNode->render(windowingMatrix);

}
