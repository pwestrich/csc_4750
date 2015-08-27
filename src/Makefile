
HEADER=
FILES = main.cpp
OBJ   = main.o

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
