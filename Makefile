AutomatedMakefile := am

# compiler information
CXX      := g++
CXXFLAGS := -g -std=c++11 -O0 -pedantic -Wall -Wextra
LDFLAGS  := 
AR 		 := ar -r

SYS := $(shell $(CXX) -dumpmachine)

.PHONY: all run clean program setup csc2110 OpenGL_Gouraud OpenGL_Textures GLSL_Adjacency GLSL_Gouraud GLSL_Multitextures

all: program csc2110 OpenGL_Gouraud OpenGL_Textures GLSL_Adjacency GLSL_Gouraud GLSL_Multitextures

run: program

	$(MAKE) -C ./src run

clean: setup

	$(MAKE) -C ./src clean
	$(MAKE) -C ./CSC2110 clean
	$(MAKE) -C ./OpenGL_Gouraud clean
	$(MAKE) -C ./OpenGL_Textures clean
	$(MAKE) -C ./GLSL_Adjacency clean
	$(MAKE) -C ./GLSL_Gouraud_Phong clean
	$(MAKE) -C ./GLSL_Multitextures clean

program: setup

	$(MAKE) -C ./src all

csc2110: setup

	$(MAKE) -C ./CSC2110

OpenGL_Gouraud: csc2110 setup

	$(MAKE) -C ./OpenGL_Gouraud all

OpenGL_Textures: csc2110 setup

	$(MAKE) -C ./OpenGL_Textures all

GLSL_Adjacency: csc2110 setup

	$(MAKE) -C ./GLSL_Adjacency all

GLSL_Gouraud: csc2110 setup

	$(MAKE) -C ./GLSL_Gouraud_Phong all

GLSL_Multitextures: csc2110 setup

	$(MAKE) -C ./GLSL_Multitextures all

setup:

ifneq (, $(findstring apple, $(SYS)))
# Do apple things
$(info System detected to be Mac OS X)

INC_DIRS := -I/usr/local/include -I/opt/X11/include -I$(PROJECT_DIR)/include
LIB_DIRS := -L/usr/local/lib -L/opt/X11/lib -L$(PROJECT_DIR)/lib
LIBS 	 := -framework OpenGL -framework GLUT -lGLEW

RM 		 := rm -f
MV 		 := mv
MAKE 	 := make

else ifneq (, $(findstring mingw, $(SYS)))
# Do mingw things
$(info System detected to be Windows MinGW)

INC_DIRS := -I$(DRIVE_LETTER)/TDM-GCC-64/include -I$(PROJECT_DIR)/include
LIB_DIRS := -L$(DRIVE_LETTER)/TDM-GCC-64/lib -L$(PROJECT_DIR)/lib
LIBS 	 := -lfreeglut -lopengl32

RM   	 := del
MV 		 := copy /Y 
MAKE 	 := mingw32-make

else ifneq (, $(findstring linux, $(SYS)))
# Do linux things
$(info System detected to be GNU/Linux)

INC_DIRS := -I$(PROJECT_DIR)/include 
LIB_DIRS := -L/usr/local/lib -L/opt/X11/lib -L$(PROJECT_DIR)/lib
LIBS 	 := 

RM 		 := rm -f
MV 		 := mv
MAKE 	 := make

$(error Set LIBS and INC_DIRS flags first before trying to build on Linux!)

else 
# Do other things
$(error Unrecongized OS)

endif

#how we build things
CXXFLAGS := $(CXXFLAGS) $(INC_DIRS)
LDFLAGS  := $(LDFLAGS) $(LIB_DIRS)
COMPILE  := $(CXX) $(CXXFLAGS) -c
LINK     := $(CXX) $(LDFLAGS) -o

#export variables so that make chains can have them
export
