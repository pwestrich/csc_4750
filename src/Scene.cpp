
#include <fstream>

#include "Scene.h"
#include "SceneNode.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

const std::string LIGHT_FILE = "./data/shade.txt";/*
const std::string OBJ_FILE   = "./data/sphere_tex.txt";
const std::string TRS_FILE   = "./data/trs.txt";
const std::string TEX_FILE   = "./data/MoonMap.raw";

const int TEX_W = 800;
const int TEX_H = 400;*/

const std::string OBJ_FILE   = "./data/cube_texture.txt";
const std::string TRS_FILE   = "./data/trs_cube.txt";
const std::string TEX_FILE   = "./data/TTU.raw";

const int TEX_W = 128;
const int TEX_H = 128;

Scene::Scene(){

	//the root scene node has no parent
	rootSceneNode = new SceneNode();

	//add lights
	const float shininess = readLights(LIGHT_FILE);

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
void Scene::render(const Matrix4 &windowingMatrix, const Vector4 &eyepoint) const {

	rootSceneNode->render(Matrix4::identity(), windowingMatrix, eyepoint, ambient, point, attenuation);

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
