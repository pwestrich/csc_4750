
#file information
HEADER := $(wildcard *.h)
FILES  := $(wildcard *.cpp)
OBJ    := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET := p0

.PHONY: all clean

all: $(TARGET)

clean:

	$(RM) $(FILES)

$(TARGET): $(OBJ)

	$(LINK) $(TARGET) $(OBJ) $(LIBS)

AffineTransforms.o:	AffineTransforms.h AffineTransforms.cpp

	$(COMPILE) AffineTransforms.cpp

Color.o: Color.h Color.cpp

	$(COMPILE) Color.cpp

Vertex.o: Vertex.h Vertex.cpp

	$(COMPILE) Vertex.cpp

Pixel.o: Pixel.h Pixel.cpp

	$(COMPILE) Pixel.cpp

Picture.o: Picture.h Picture.cpp

	$(COMPILE) Picture.cpp

Window.o: Window.h Window.cpp

	$(COMPILE) Window.cpp

Main.o:	Main.cpp

	$(COMPILE) Main.cpp
