
#include "InstanceObject.h"
#include "BasicObject.h"
#include "Matrix4.h"

InstanceObject::~InstanceObject(){}

//used to build up several transforms
void InstanceObject::buildTransform(const Matrix4 &newTransform){

	//take the incoming matrix, and multiply the current transform by it
	instanceTransform = newTransform * instanceTransform;

}

//renders the object using the current instance transform
void InstanceObject::render(){

	//tell the BasicObject to render with the instance transform
	parent->render(instanceTransform);

}
