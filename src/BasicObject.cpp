
#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

#include "utilities.h"
#include "BasicObject.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "Texture.h"
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
void BasicObject::render(const Matrix4 &transform, const Texture &tex, const Texture &bumpMap) const {

	//turn off number 0
	glClientActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//set texture
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 1);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.getWidth(), tex.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, tex.getData());

	//set bump map
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, 3);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bumpMap.getWidth(), bumpMap.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bumpMap.getData());

	//set the transform
	float *transformColumnMajor = transform.transposeValues();
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glMultMatrixf(transformColumnMajor);

	//set the color/texture
	const float material[] = {1, 1, 1, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	//draw the object
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verticies);
	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, faces);

	//undo matrix
	glPopAttrib();
	glPopMatrix();

	delete [] transformColumnMajor;

}
