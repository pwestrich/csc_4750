
#file information
FILES = AffineTransforms.o Color.o Vertex.o Pixel.o Picture.o Window.o Main.o
EXE_NAME = p0

.PHONY: all clean 4750_Start

all: 4750_Start

clean:

	$(RM) $(FILES)

4750_Start: 		$(FILES)
			$(LINK) $(EXE_NAME) $(FILES) $(LIBS)

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
