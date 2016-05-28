# The make file of the project PH7

# list of command line flags
GLFLGS = -lm -lglut -lGLEW -lGL -lGLU

# list of G++ compiler flags
CXXFLGS = -g -O2 -Wall -std=c++11

MODULES= src/Init.cpp src/Keyboard.cpp

# dependent headers
HEADERS=./incs/*.h

# the path of include files
INCLUDES= -I./incs -I./libs/Angel/include -I./libs/rply

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
	echo "PH7: Building the virtual museum ..."
	g++ -o $(EXEC) $(INCLUDES) InitShader.o rply.o $(SRC)/ph7Main.cpp $(MODULES) $(CXXFLGS) $(GLFLGS)

# compile the init shader, the InitShader code is used as is from Angel
InitShader.o: $(LIBS)/Angel/InitShader.cpp
	g++ -c -Wall $(LIBS)/Angel/InitShader.cpp $(INCLUDES) -o InitShader.o

# compile the rply parser, its code is in libs/rply
rply.o: $(LIBS)/rply/rply.c
	gcc -c $(LIBS)/rply/rply.c $(INCLUDES) -o rply.o

# remove object files
clean:
	rm *.o *$(EXEC)

