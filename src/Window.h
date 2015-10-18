
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "Matrix4.h"

class Scene;

class Window {

private:

	//have we made the window yet?
	bool init;

	//the current scene
	Scene *scene;

	//the field of view, in radians
	float fov;

	//the normalization and camera matricies
	Matrix4 normalMatrix;
	Matrix4 cameraMatrix;

	//the z-buffer
	float *zBuffer;
	int zBufferSize;

	Window();

	//returns the matrix to convert window coordinates to screen coordinates
	Matrix4 getWindowingMatrix() const;

	//returns the normal matrix
	Matrix4 createNormalMatrix(const std::string &filename);

	//returns the aspect ratio matrix
	Matrix4 getAspectRatioMatrix() const;

	//returns the camera matrix
	Matrix4 createCameraMatrix(const std::string &filename) const;

public:

	//the window shall be singleton only
	static Window *getWindow();

	~Window();

	//creates a window for us to draw in
	void initWindow(const int argc, const char **argv, const int width, const int height, const int x, const int y, 
					const char *title, const std::string &normalFile, const std::string &cameraFile);

	//displays the window on screen
	void show();

	void render();

	//draws one pixel on the screen. takes window coordinates.
	void drawPixel(const int x, const int y, const float z, const float r, const float g, const float b);

	//get the width and height of the window 
	int getWidth() const;
	int getHeight() const;

};

#endif
