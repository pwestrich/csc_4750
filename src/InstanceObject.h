
#ifndef INSTANCE_OBJECT_H
#define INSTANCE_OBJECT_H

#include <memory>

#include "Matrix4.h"

class BasicObject;

class InstanceObject {

private:

	//reference to the parent BasicObject
	//this cannot be deleted until all instance objects are deleted.
	std::shared_ptr<BasicObject> parent;

	//the instance transform of the object
	Matrix4 instanceTransform;

public:

	//constructs the InstanceObject with its parent and optional initial transform
	InstanceObject(std::shared_ptr<BasicObject> obj) : InstanceObject(obj, Matrix4::identity()){}
	InstanceObject(std::shared_ptr<BasicObject> obj, const Matrix4 &transform) : parent(obj), instanceTransform(transform){}

	//used to build up several transforms
	void buildTransform(const Matrix4 &newTransform);

	//renders the object using the current instance transform
	void render(const Matrix4 &transform) const;

};

#endif
