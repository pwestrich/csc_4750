
HEADER := $(wildcard *.h)
FILES  := $(wildcard *.cpp)
OBJ    := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET := sphere_main

.PHONY: all clean run

run: all

clean:

	$(RM) *.o
	$(RM) %(TARGET)

run: all

all: $(TARGET)

$(TARGET): $(OBJ)

	$(LINK) $(TARGET) sphere_main.o ../Vector4.o ../utilities.o $(LIBS)

sphere_main.o: sphere_main.cpp ../Vector4.h ../utilities.h

	$(COMPILE) sphere_main.cpp
