
#include <fstream>

#include "Scene.h"
#include "SceneNode.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

Scene::Scene(){

	//the root scene node has no parent
	rootSceneNode = new SceneNode();

	//add lights
	const float shininess = readLights("shade.txt");

	//create the absic objects for the robot
	//BasicObject *basicCube = new BasicObject("cube.txt");
	//BasicObject *basicCylinder = new BasicObject("cylinder.txt");
	BasicObject *basicSphere = new BasicObject("sphere.txt", shininess);

	//objects.push_back(basicCube);
	//objects.push_back(basicCylinder);
	objects.push_back(basicSphere);

	InstanceObject *sphere = new InstanceObject(basicSphere, "trs.txt");

	rootSceneNode->addChildObject(sphere);

	instances.push_back(sphere);

	/*
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
	*/

}

Scene::~Scene(){

	delete rootSceneNode;

}

//renders every InstanceObjectgiven the windowing matrix
void Scene::render(const Matrix4 &windowingMatrix, const Vector4 &eyepoint) const {

	rootSceneNode->render(Matrix4::identity(), windowingMatrix, eyepoint, attenuation);

}

//private methods below here ----------------------------------------------------------------------
float Scene::readLights(const std::string &filename){

	std::fstream inFile(filename);

	if (!inFile){

		std::cerr << "Invalid filename: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	std::string buffer;
	std::vector<std::string> lines;

	do {

		getline(inFile, buffer);
		lines.push_back(buffer);

	} while (!inFile.eof());

	/*if (lines.size() != 12){

		std::cerr << "Error: File invalid: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}*/

	//lines 1, 2, 3 are the point light's position
	const float px = stof(lines[1]);
	const float py = stof(lines[2]);
	const float pz = stof(lines[3]);

	//lines 5, 6, 7 are the ambient light color
	const float ar = stof(lines[5]);
	const float ag = stof(lines[6]);
	const float ab = stof(lines[7]);

	//line 9 is linear attenuation
	attenuation = stof(lines[9]);

	//line 11 is the shininess
	const float shininess = stof(lines[11]);

	//assume point light is white, and the ambient is a zero, because it dioesn't amtter
	point = Light(1.0, 1.0, 1.0, px, py, pz);
	ambient = Light(ar, ag, ab, 0.0, 0.0, 0.0);

	return shininess;

}
