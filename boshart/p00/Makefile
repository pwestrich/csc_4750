AutomatedMakefile = am
CC = g++

INC_DIRS = -I../../CSC2110 -I/usr/local/include -I/opt/X11/include
LIB_DIRS = -L../../CSC2110 -I/usr/local/lib -I/opt/X11/lib
LIBS =  -framework OpenGL -framework GLUT -lCSC2110

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

FILES = AffineTransforms.o Color.o Vertex.o Pixel.o Picture.o Window.o Main.o
all: 4750_Start

4750_Start: 		$(FILES)
			$(LINK) P0 $(FILES) $(LIBS)

AffineTransforms.o:	AffineTransforms.h AffineTransforms.cpp
			$(COMPILE) AffineTransforms.cpp

Color.o:		Color.h Color.cpp
			$(COMPILE) Color.cpp

Vertex.o:		Vertex.h Vertex.cpp
			$(COMPILE) Vertex.cpp

Pixel.o:		Pixel.h Pixel.cpp
			$(COMPILE) Pixel.cpp

Picture.o:		Picture.h Picture.cpp
			$(COMPILE) Picture.cpp

Window.o:		Window.h Window.cpp
			$(COMPILE) Window.cpp

Main.o:			Main.cpp
			$(COMPILE) Main.cpp
