
#include "window.h"

const char *title = "CSC 4750";

int main(const int argc, const char **argv){

	Window win(argc, argv, 1280, 768, 0, 0, title);
	win.show();

	return 0;

}