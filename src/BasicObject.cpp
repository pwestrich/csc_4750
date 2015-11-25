
#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

#include "utilities.h"
#include "BasicObject.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "ReadObject.h"	//shamelessly stolen from Dr. Boshart

//reads in an object from a .obj file
BasicObject::BasicObject(const std::string &filename, const float _shininess){

	shininess    = _shininess;

	_numVerticies = numVertices(filename.c_str());
	_numFaces 	  = numFaces(filename.c_str());
	_indexCount   = _numFaces * 3;

	verticies 	  = getVertices(filename.c_str(), _numVerticies);
	normals 	  = getNormals(filename.c_str(), _numVerticies);
	faces 		  = getFaces(filename.c_str(), _numFaces);
	texCoords 	  = getTextureCoords(filename.c_str(), _numVerticies);

}

BasicObject::~BasicObject(){

	delete [] texCoords;
	delete [] faces;
	delete [] normals;
	delete [] verticies;

}

//draws the object
void BasicObject::render(const Matrix4 &transform, const Texture &tex) const {

	//set the transform
	float *transformColumnMajor = transform.transposeValues();
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glMultMatrixf(transformColumnMajor);

	//set the color/texture
	const float material[] = {1, 0, 0, 0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verticies);
	glNormalPointer(GL_FLOAT, 0, normals);

	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, faces);

	//undo matrix
	glPopAttrib();
	glPopMatrix();

	delete [] transformColumnMajor;

}
