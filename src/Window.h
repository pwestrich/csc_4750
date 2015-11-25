
#ifndef WINDOW_H
#define WINDOW_H

#include "Vector4.h"
#include "Matrix4.h"

class Scene;

class Window {

private:

	//have we made the window yet?
	bool init;

	//the current scene
	Scene *scene;

	Window();

public:

	//the window shall be singleton only
	static Window *getWindow();

	~Window();

	//creates a window for us to draw in
	void initWindow(const int argc, const char **argv, const int width, const int height, const int x, const int y, const char *title);

	//displays the window on screen
	void show();

	void render();

	//get the width and height of the window 
	int getWidth() const;
	int getHeight() const;

};

#endif
