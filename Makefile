AutomatedMakefile := am

# compiler information
CC      := g++
CCFLAGS := -g -std=c++11 -O2
AR 		:= ar -r

SYS := $(shell $(CC) -dumpmachine)

.PHONY: all run clean csc2110 boshart program setup

all: csc2110 boshart program

run: program

	make -C ./src run

clean: setup

	make -C ./boshart/p00 clean
	make -C ./src clean

setup:

ifneq (, $(findstring apple, $(SYS)))
# Do apple things
$(info System detected to be Mac OS X)

INC_DIRS := -I$(PROJECT_DIR)/include -I/usr/local/include -I/opt/X11/include
LIB_DIRS := -L$(PROJECT_DIR)/lib -L/usr/local/lib -L/opt/X11/lib
LIBS 	 :=  -framework OpenGL -framework GLUT -lCSC2110

RM 		 := rm -f
MV 		 := mv
MAKE 	 := make

else ifneq (, $(findstring mingw, $(SYS)))
# Do mingw things
$(info System detected to be Windows MinGW)

INC_DIRS := -I$(PROJECT_DIR)/include -I$(DRIVE_LETTER)/TDM-GCC-64/include
LIB_DIRS := -L$(PROJECT_DIR)/lib -L$(DRIVE_LETTER)/TDM-GCC-64/lib
LIBS 	 := -lCSC2110 -lfreeglut -lopengl32

RM   	 := del
MV 		 := copy /Y 
MAKE 	 := mingw32-make

else ifneq (, $(findstring linux, $(SYS)))
# Do linux things
$(info System detected to be GNU/Linux)

INC_DIRS := -I$(PROJECT_DIR)/include 
LIB_DIRS := -L$(PROJECT_DIR)/lib -L/usr/local/lib -L/opt/X11/lib
LIBS 	 :=  -lCSC2110

RM 		 := rm -f
MV 		 := mv
MAKE 	 := make

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

all: setup boshart program

csc2110: setup

	$(MAKE) -C ./CSC2110 all

boshart: setup csc2110

	$(MAKE) -C ./boshart/p00 all

program: setup

	$(MAKE) -C ./src all
