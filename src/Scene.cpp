
#include <GL/glut.h>

#include "Scene.h"
#include "SceneNode.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

const std::string LIGHT_FILE  = "./data/shade.txt";
const std::string OBJ_FILE    = "./data/sphere_texture.txt";
const std::string TRS_FILE    = "./data/trs.txt";
const std::string TEX_FILE    = "./data/MoonColor.raw";
const std::string BUMP_FILE   = "./data/MoonNormal.raw";
const std::string NORMAL_FILE = "./data/fov.txt";
const std::string CAMERA_FILE = "./data/camera.txt";

const int TEX_W = 512;
const int TEX_H = 256;

const int BUMP_W = 512;
const int BUMP_H = 256;

const Vector4 EYEPOINT(0.0, 0.0, 4.0, 1.0);
const Vector4 ATPOINT(0.0, 0.0, 0.0, 1.0);
const Vector4 LIGHT_LOCATION(-2.0, -5.0, 4.0, 1.0);
const Vector4 LIGHT_COLOR(1.0, 1.0, 1.0, 1.0);
const Vector4 LIGHT_AMBIENT(0.03, 0.03, 0.03, 1.0);
const Vector4 AMBIENT_COLOR(1.0, 0.0, 0.0, 1.0);
const float SHININESS = 1.0;

Scene::Scene(){

	//the root scene node has no parent
	rootSceneNode = new SceneNode();

	BasicObject *basicSphere = new BasicObject(OBJ_FILE, SHININESS);
	objects.push_back(basicSphere);

	InstanceObject *sphere = new InstanceObject(basicSphere, TRS_FILE, TEX_FILE, BUMP_FILE, TEX_W, TEX_H, BUMP_W, BUMP_H);
	rootSceneNode->addChildObject(sphere);
	instances.push_back(sphere);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(EYEPOINT.x(), EYEPOINT.y(), EYEPOINT.z(), ATPOINT.x(), ATPOINT.y(), ATPOINT.z(), 0.0, 1.0, 0.0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LIGHT_AMBIENT.getValues());
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_LOCATION.getValues());
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_COLOR.getValues());

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_COLOR.getValues());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LIGHT_COLOR.getValues());

}

Scene::~Scene(){

	delete rootSceneNode;

}

//renders every InstanceObjectgiven the windowing matrix
void Scene::render() const {

	rootSceneNode->render(Matrix4::identity());

}

//private methods below here ----------------------------------------------------------------------

