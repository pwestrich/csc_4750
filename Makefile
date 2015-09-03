AutomatedMakefile = am

# compiler information
CC      = g++
CCFLAGS = -g -std=c++11 -O2
AR 		= ar -r

SYS = $(shell gcc -dumpmachine)
ifneq (, $(findstring linux, $(SYS)))
	# Do linux things
	INC_DIRS = -I$(PROJECT_DIR)/include 
	LIB_DIRS = -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
	LIBS 	 =  -lCSC2110

	RM 		 = rm -f
	MV 		 = mv

	$(error Set LIBS and INC_DIRS flags first!)

else ifneq(, $(findstring mingw, $(SYS)))
	# Do mingw things
	INC_DIRS = -I$(PROJECT_DIR)/include 
	LIB_DIRS = -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
	LIBS 	 = -lCSC2110

	RM   	 = del
	MV 		 = move

	$(error Set LIBS and INC_DIRS flags first!)

else ifneq(, $(findstring cygwin, $(SYS)))
	# Do cygwin things
	INC_DIRS = -I$(PROJECT_DIR)/include 
	LIB_DIRS = -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
	LIBS 	 = -lCSC2110

	RM 		 = del
	MV 		 = move

	$(error Set LIBS and INC_DIRS flags first!)

else ifneq(, $(findstring apple, $(SYS)))
 	# Do apple things
	INC_DIRS = -I$(PROJECT_DIR)/include -I/usr/local/include -I/opt/X11/include
	LIB_DIRS = -L$(PROJECT_DIR)/lib -I/usr/local/lib -I/opt/X11/lib
	LIBS 	 =  -framework OpenGL -framework GLUT -lCSC2110

	RM 		 = rm -f
	MV 		 = mv

else 
	# Do other things
	$(error Unrecongized OS)

endif

#how we build things
COMPILE = $(CC) $(CCFLAGS) $(INC_DIRS) -c
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
