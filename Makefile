AutomatedMakefile = am

#utility information
CC = g++ -std=c++11
RM = rm -f
AR = ar -r
MV = mv

#include and library directories
INC_DIRS = -I$(PROJECT_DIR)/include -I/usr/local/include -I/opt/X11/include
LIB_DIRS = -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
LIBS =  -framework OpenGL -framework GLUT -lCSC2110

#how we build things
COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

#export variables so that make chains can have them
export

.PHONY: all run clean csc2110 boshart program

all: csc2110 boshart program

run: all

	make -C ./src run

clean:

	make -C ./boshart/p00 clean

csc2110:

	make -C ./CSC2110 all

boshart:

	make -C ./boshart/p00 all

program: csc2110

	make -C ./src all

