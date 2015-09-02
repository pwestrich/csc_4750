
#include "Window.h"

const char *title = "CSC 4750";

int main(const int argc, const char **argv){

	Window *win = Window::getWindow();

	win->initWindow(argc, argv, 800, 600, 25, 25, title);
	win->show();

	delete win;

	return 0;

}
