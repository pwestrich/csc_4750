
#include <string>

#include "Window.h"

const int x = 800;
const int y = 600;
const char *title = "CSC 4750";

int main(const int argc, const char **argv){

	Window *win = Window::getWindow();

	win->initWindow(argc, argv, x, y, 25, 25, title);
	win->show();

	return 0;

}
