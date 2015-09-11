
#include "Window.h"
#include "Picture.h"
#include "BasicObject.h"
#include "Matrix4.h"

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

	const Window *win = Window::getWindow();

	const Matrix4 aspect = win->getAspectRatioMatrix();
	const Matrix4 windowing = win->getWindowingMatrix();

	const Matrix4 transform = windowing * aspect;

	for (int i = 0; i < objects.size(); ++i){

		objects[i]->render(transform);

	}

}
