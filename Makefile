AutomatedMakefile := am

# compiler information
CC      := g++
CCFLAGS := -g -std=c++11 -O2
AR 		:= ar -r

SYS := $(shell $(CC) -dumpmachine)

.PHONY: all run clean csc2110 boshart program setup

all: csc2110 boshart program

run: all

	make -C ./src run

clean: setup

	make -C ./boshart/p00 clean
	make -C ./src clean

setup:

ifneq (, $(findstring apple, $(SYS)))
# Do apple things
$(info System detected to be Mac OS X)

INC_DIRS := -I$(PROJECT_DIR)/include -I/usr/local/include -I/opt/X11/include
LIB_DIRS := -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
LIBS 	 :=  -framework OpenGL -framework GLUT -lCSC2110

RM 		 := rm -f
MV 		 := mv

else ifneq (, $(findstring mingw, $(SYS)))
# Do mingw things
$(info System detected to be Windows MinGW)

INC_DIRS := -I$(PROJECT_DIR)/include 
LIB_DIRS := -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
LIBS 	 := -lCSC2110

RM   	 := del
MV 		 := move

$(error Set LIBS and INC_DIRS flags first before building with MinGW!)

else ifneq (, $(findstring cygwin, $(SYS)))
# Do cygwin things
$(info System detected to be Windows CyGWin)

INC_DIRS := -I$(PROJECT_DIR)/include 
LIB_DIRS := -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
LIBS 	 := -lCSC2110

RM 		 := del
MV 		 := move

$(error Set LIBS and INC_DIRS flags first before building with CyGWin!)

else ifneq (, $(findstring linux, $(SYS)))
# Do linux things
$(info System detected to be GNU/Linux)

INC_DIRS := -I$(PROJECT_DIR)/include 
LIB_DIRS := -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
LIBS 	 :=  -lCSC2110

RM 		 := rm -f
MV 		 := mv

$(error Set LIBS and INC_DIRS flags first before trying to build on Linux!)

else 
# Do other things
$(error Unrecongized OS)

endif

#how we build things
COMPILE := $(CC) $(CCFLAGS) $(INC_DIRS) -c
LINK := $(CC) $(LIB_DIRS) -o

#export variables so that make chains can have them
export

csc2110: setup

	make -C ./CSC2110 all

boshart: setup

	make -C ./boshart/p00 all

program: setup csc2110

	make -C ./src all
