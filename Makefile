##/////////////////////////////////////////////////////////////////////
##
##                   COMP 510, Computer Graphics, Spring 2016
##                              Final project
##                PH7: A virtual Museum Based on OpenGL and Glut
##
##                            (c) 2016, 2017, 2018 - Hassan & Pirah.
##            Copying without the authors consent is strictly prohibited.
##
##/////////////////////////////////////////////////////////////////////
##
##   The make file of the project PH7.
##
##/////////////////////////////////////////////////////////////////////


# list of command line flags
GLFLGS = -lm -lglut -lGLEW -lGL -lGLU

# list of G++ compiler flags
CXXFLGS = -g -O2 -Wall -std=c++11 -Wno-strict-aliasing -Wno-unused-result

MODULES= src/Init.cpp src/Keyboard.cpp

# dependent headers
HEADERS=./incs/*.h ./incs/antiquity/*.h ./incs/room/*.h

# the path of include files
INCLUDES= -I./incs -I./incs/room -I./incs/antiquity -I./libs/Angel/include -I./libs/rply

# path  to sources
SRC=src

# path to libraries
LIBS=libs

# name of final executable
EXEC=ph7Museum

# compile the project
all: $(EXEC)

# build the final execuatable
$(EXEC): InitShader.o rply.o $(SRC)/ph7Main.cpp $(MODULES) $(HEADERS)
	$(info ============================================== )
	$(info PH7: Building the virtual museum ...)
	g++ -o $(EXEC) $(INCLUDES) bin/InitShader.o bin/rply.o $(SRC)/ph7Main.cpp $(MODULES) $(CXXFLGS) $(GLFLGS)

# compile the init shader, the InitShader code is used as is from Angel
InitShader.o: $(LIBS)/Angel/InitShader.cpp
	$(info ============================================== )
	$(info Compiling the graphics shaders...)
	g++ -c -g -Wall $(LIBS)/Angel/InitShader.cpp $(INCLUDES) -o bin/InitShader.o

# compile the rply parser, its code is in libs/rply
rply.o: $(LIBS)/rply/rply.c
	$(info ============================================== )
	$(info Compiling the rply parser library...)
	gcc -c -g $(LIBS)/rply/rply.c $(INCLUDES) -o bin/rply.o

# remove object files
clean:
	rm -f *.o *$(EXEC)
