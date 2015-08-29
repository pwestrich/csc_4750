
HEADER= utilities.h window.h Vector3.h Matrix3.h Vertex.h Face.h BasicObject.h
FILES = main.cpp utilities.cpp window.cpp Vector3.cpp Matrix3.cpp Vertex.cpp Face.cpp BasicObject.cpp
OBJ   = main.o utilities.o window.o Vector3.o Matrix3.o Vertex.o Face.o BasicObject.o

TARGET=program

.PHONY: all clean run

all: $(OBJ) $(HEADER) $(FILES)

	$(LINK) $(TARGET) $(OBJ) $(LIBS)

run: all

	./$(TARGET)

clean:

	$(RM) $(OBJ) $(TARGET)

main.o: main.cpp $(HEADER)

	$(COMPILE) main.cpp

utilities.o: utilities.h

	$(COMPILE) utilities.cpp

window.o: window.cpp window.h

	$(COMPILE) window.cpp

Vector3.o: Vector3.cpp Vector3.h

	$(COMPILE) Vector3.cpp

Matrix3.o: Matrix3.cpp Matrix3.h Vector3.h

	$(COMPILE) Matrix3.cpp

Vertex.o: Vertex.cpp Vertex.h Vector3.h

	$(COMPILE) Vertex.cpp

Face.o: Face.cpp Face.h Vertex.h Vector3.h

	$(COMPILE) Face.cpp

BasicObject.o: BasicObject.cpp BasicObject.h Face.h Vertex.h Vector3.h

	$(COMPILE) BasicObject.cpp
