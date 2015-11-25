
#include <fstream>

#include "Scene.h"
#include "SceneNode.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

const std::string LIGHT_FILE  = "./data/shade.txt";
const std::string OBJ_FILE    = "./data/sphere_texture.txt";
const std::string TRS_FILE    = "./data/trs.txt";
const std::string TEX_FILE    = "./data/MoonMap.raw";
const std::string NORMAL_FILE = "./data/fov.txt";
const std::string CAMERA_FILE = "./data/camera.txt";

const int TEX_W = 800;
const int TEX_H = 400;

Scene::Scene(){

	//the root scene node has no parent
	rootSceneNode = new SceneNode();

	float shininess = 1.0;

	BasicObject *basicSphere = new BasicObject(OBJ_FILE, shininess);

	objects.push_back(basicSphere);

	InstanceObject *sphere = new InstanceObject(basicSphere, TRS_FILE, TEX_FILE, TEX_W, TEX_H);

	rootSceneNode->addChildObject(sphere);

	instances.push_back(sphere);

}

Scene::~Scene(){

	delete rootSceneNode;

}

//renders every InstanceObjectgiven the windowing matrix
void Scene::render() const {

	rootSceneNode->render(Matrix4::identity());

}

//private methods below here ----------------------------------------------------------------------

