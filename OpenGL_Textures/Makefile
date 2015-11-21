
#files in the folder
HEADER := $(wildcard *.h)
FILES  := $(wildcard *.cpp)
OBJ    := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET := main_gl_textures

.PHONY: all clean run

all: $(TARGET)

clean:

	$(RM) $(OBJ)
	$(RM) $(TARGET)

run: all

	./$(TARGET)

$(TARGET): $(OBJ)

	$(LINK) $(TARGET) $(OBJ) $(LIBS) -lCSC2110

Texture.o:		Texture.h Texture.cpp
			$(COMPILE) Texture.cpp

ReadObject.o:		ReadObject.h ReadObject.cpp
			$(COMPILE) ReadObject.cpp

AffineTransforms.o:	AffineTransforms.h AffineTransforms.cpp
			$(COMPILE) AffineTransforms.cpp

Color.o:		Color.h Color.cpp
			$(COMPILE) Color.cpp

Vertex.o:		Vertex.h Vertex.cpp
			$(COMPILE) Vertex.cpp

Vector.o:		Vector.h Vector.cpp
			$(COMPILE) Vector.cpp

BasicObject.o:		BasicObject.h BasicObject.cpp
			$(COMPILE) BasicObject.cpp

InstanceObject.o:	InstanceObject.h InstanceObject.cpp
			$(COMPILE) InstanceObject.cpp

Scene.o:		Scene.h Scene.cpp
			$(COMPILE) Scene.cpp

Picture.o:		Picture.h Picture.cpp
			$(COMPILE) Picture.cpp

Window.o:		Window.h Window.cpp
			$(COMPILE) Window.cpp

DeleteObject.o:		DeleteObject.h DeleteObject.cpp
			$(COMPILE) DeleteObject.cpp

Node.o:			Node.h Node.cpp
			$(COMPILE) Node.cpp

TransformNode.o:	TransformNode.h TransformNode.cpp
			$(COMPILE) TransformNode.cpp

Light.o:		Light.h Light.cpp
			$(COMPILE) Light.cpp

Main.o:			Main.cpp
			$(COMPILE) Main.cpp

