#include "Window.h"

int main(int argc, char** argv)
{
   const char* title = "OpenGL Lighting";
   Window window(argc, argv, 800, 600, 450, 250, title);
   window.show();
   return 0;
}
