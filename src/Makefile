
HEADER= window.h
FILES = main.cpp window.cpp
OBJ   = main.o window.o

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

window.o: window.cpp window.h

	$(COMPILE) window.cpp
