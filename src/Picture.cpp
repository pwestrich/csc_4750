
#include "Picture.h"
#include "BasicObject.h"

//singletons everywhere
Picture::Picture(){

	BasicObject *obj = new BasicObject("sphere.txt");
	objects.push_back(obj);

}

Picture *Picture::getPicture(){

	static Picture pic;
	return &pic;

}

Picture::~Picture(){}

//renders the picture
void Picture::render(){

	for (int i = 0; i < objects.size(); ++i){

		objects[i]->render();

	}

}
