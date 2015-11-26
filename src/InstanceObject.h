
#ifndef INSTANCE_OBJECT_H
#define INSTANCE_OBJECT_H

#include <string>

#include "Vector4.h"
#include "Matrix4.h"
#include "Texture.h"

class BasicObject;

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
	const Texture bumpMap;

public:

	//constructs the InstanceObject with its parent and optional initial transform
	InstanceObject(const BasicObject *obj, const Matrix4 &transform, const std::string &texFilename, 
				   const std::string &bumpMapFilename, const int tw, const int th, const int bw, const int bh) 
		: parent(obj), instanceTransform(transform), material(1.0, 1.0, 1.0, 0.0), tex(texFilename, tw, th), bumpMap(bumpMapFilename, bw, bh){}

	//optional constructor to accept a transformation file
	InstanceObject(const BasicObject *obj, const std::string &filename, const std::string &texFilename, 
				   const std::string &bumpMapFilename, const int tw, const int th, const int bw, const int bh);

	//used to build up several transforms
	void buildTransform(const Matrix4 &newTransform);

	//renders the object using the current instance transform
	void render(const Matrix4 &transform) const;

};

#endif
