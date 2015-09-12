
#ifndef WINDOW_H
#define WINDOW_H

#include <memory>

class Matrix4;
class Scene;

class Window {

private:

	//have we made the window yet?
	bool init;

	//the current scene
	std::shared_ptr<Scene> scene;

	Window();

public:

	//the window shall be singleton only
	static Window *getWindow();

	//creates a window for us to draw in
	void initWindow(const int argc, const char **argv, const int width, const int height, const int x, const int y, const char *title);

	//displays the window on screen
	void show();

	void render() const;

	//draws one pixel on the screen. takes window coordinates.
	void drawPixel(const int x, const int y, const float r, const float g, const float b) const;

	//get the width and height of the window 
	int getWidth() const;
	int getHeight() const;

	//returns the matrix to convert window coordinates to screen coordinates
	Matrix4 getWindowingMatrix() const;

	//returns the aspect matrix
	Matrix4 getAspectRatioMatrix() const;

};

#endif
