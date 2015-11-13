
#ifndef INSTANCE_OBJECT_H
#define INSTANCE_OBJECT_H

#include <string>

#include "Vector4.h"
#include "Matrix4.h"
#include "Texture.h"

class BasicObject;
class Light;

class InstanceObject {

private:

	//reference to the parent BasicObject
	//this cannot be deleted until all instance objects are deleted.
	const BasicObject *parent;

	//the instance transform of the object
	Matrix4 instanceTransform;

	//the object's material color
	Vector4 material;

	const Texture tex;

public:

	//constructs the InstanceObject with its parent and optional initial transform
	InstanceObject(const BasicObject *obj, const Matrix4 &transform, const std::string &texFilename, const int tw, const int th) 
		: parent(obj), instanceTransform(transform), material(1.0, 1.0, 1.0, 0.0), tex(texFilename, tw, th){}

	//optional constructor to accept a transformation file
	InstanceObject(const BasicObject *obj, const std::string &filename, const std::string &texFilename, const int tw, const int th);

	//used to build up several transforms
	void buildTransform(const Matrix4 &newTransform);

	//renders the object using the current instance transform
	void render(const Matrix4 &transform, const Matrix4 &windowingMatrix, const Vector4 &eyepoint, 
				const Light &ambient, const Light &point,  const float attenuation) const;

};

#endif
