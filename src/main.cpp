
#include <string>

#include "Window.h"

const int x = 800;
const int y = 600;
const char *title = "CSC 4750";
const std::string normalFile("./data/fov.txt");
const std::string cameraFile("./data/camera.txt");

int main(const int argc, const char **argv){

	Window *win = Window::getWindow();

	win->initWindow(argc, argv, x, y, 25, 25, title, normalFile, cameraFile);
	win->show();

	return 0;

}
