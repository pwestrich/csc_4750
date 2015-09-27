
HEADER := $(wildcard *.h)
FILES  := $(wildcard *.cpp)
OBJ    := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET = program

.PHONY: all clean run

all: $(TARGET)

run: all

	./$(TARGET)

clean:

	$(RM) $(OBJ) $(TARGET)

$(TARGET): $(OBJ) $(HEADER) $(FILES)

	$(LINK) $(TARGET) $(OBJ) $(LIBS)

main.o: main.cpp Window.h

	$(COMPILE) main.cpp

utilities.o: utilities.h

	$(COMPILE) utilities.cpp

Window.o: Window.cpp Window.h Matrix4.h Vector4.h Scene.h

	$(COMPILE) Window.cpp

Vector4.o: Vector4.cpp Vector4.h

	$(COMPILE) Vector4.cpp

Matrix4.o: Matrix4.cpp Matrix4.h Vector4.h

	$(COMPILE) Matrix4.cpp

AffineTransformations.o: AffineTransformations.cpp AffineTransformations.h Vector4.h Matrix4.h

	$(COMPILE) AffineTransformations.cpp

Face.o: Face.cpp Face.h Vector4.h Window.h

	$(COMPILE) Face.cpp

BasicObject.o: BasicObject.cpp BasicObject.h Face.h Vector4.h Matrix4.h

	$(COMPILE) BasicObject.cpp

InstanceObject.o: InstanceObject.cpp InstanceObject.h BasicObject.h Matrix4.h Vector4.h

	$(COMPILE) InstanceObject.cpp

Scene.o: Scene.cpp Scene.h Matrix4.h BasicObject.h InstanceObject.h SceneNode.h

	$(COMPILE) Scene.cpp

SceneNode.o: SceneNode.cpp SceneNode.h InstanceObject.h Matrix4.h

	$(COMPILE) SceneNode.cpp
