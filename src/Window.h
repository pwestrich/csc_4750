
#ifndef WINDOW_H
#define WINDOW_H

class Window {

private:

	//have we made the window yet?
	bool init;

	Window();

public:

	static Window *getWindow();

	~Window();

	//creates a window for us to draw in
	void initWindow(const int argc, const char**argv, const int width, const int height, const int x, const int y, const char *title);

	//displays the window on screen
	void show();

	//draws one pixel on the screen, converting it to window coordinates
	void drawPixel(const int x, const int y, const float r, const float g, const float b);

};

#endif
