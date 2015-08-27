
#ifndef WINDOW_H
#define WINDOW_H

class Window {

private:


public:

	//creates a window for us to draw in
	Window(const int argc, const char**argv, const int width, const int height, const int x, const int y, const char *title);
	~Window();

	//displays the window on screen
	void show();

};

#endif
