
#include <string>

#include "Window.h"

const char *title = "CSC 4750";
const std::string normalFile("fov.txt");
const std::string cameraFile("camera.txt");

int main(const int argc, const char **argv){

	Window *win = Window::getWindow();

	win->initWindow(argc, argv, 1280, 768, 25, 25, title, normalFile, cameraFile);
	win->show();

	delete win;

	return 0;

}
