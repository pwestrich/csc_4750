
#files in the folder
FILES = ReadFile.cpp WriteFile.cpp Keyboard.cpp Matrix.cpp Poly.cpp Integer.cpp Double.cpp Permutation.cpp
OBJ   = ReadFile.o WriteFile.o Keyboard.o Matrix.o Poly.o Integer.o Double.o Permutation.o

LIB_NAME = libCSC2110.a

.PHONY: all install clean

all: install

install: $(OBJ)

	$(AR) $(LIB_NAME) $(OBJ)
	$(MV) $(LIB_NAME) $(PROJECT_DIR)/lib/$(LIB_NAME)

clean:

	$(RM) $(OBJ)
	$(RM) $(PROJECT_DIR)/lib/$(LIB_NAME)

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

