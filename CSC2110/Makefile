
#files in the folder
HEADER := $(wildcard *.h)
FILES  := $(wildcard *.cpp)
OBJ    := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET = libCSC2110.a

.PHONY: all install clean

all: install

install: $(TARGET)

	$(MV) $(TARGET) ../lib/$(TARGET)

clean:

	$(RM) $(OBJ)
	$(RM) $(TARGET)
	$(RM) $(PROJECT_DIR)/lib/$(TARGET)

$(TARGET): $(OBJ)

	$(AR) $(TARGET) $(OBJ)

ReadFile.o: ReadFile.cpp

	$(COMPILE) ReadFile.cpp

WriteFile.o: WriteFile.cpp

	$(COMPILE) WriteFile.cpp

Keyboard.o: Keyboard.cpp

	$(COMPILE) Keyboard.cpp

Matrix.o: Matrix.cpp

	$(COMPILE) Matrix.cpp

Poly.o: Poly.cpp

	$(COMPILE) Poly.cpp

Integer.o: Integer.cpp

	$(COMPILE) Integer.cpp

Double.o: Double.cpp

	$(COMPILE) Double.cpp

Permutation.o: Permutation.cpp

	$(COMPILE) Permutation.cpp

#generic rule for anything missed
%.o: %.cpp %.h

	$(COMPILE) $<

