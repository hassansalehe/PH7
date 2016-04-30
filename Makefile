# The make file of the project PH7

# list of command line flags
GLFLGS = -lm -lglut -lGLEW -lGL -lGLU

# list of G++ compiler flags
CXXFLGS = -g -O2 -Wall

MODULES= src/Init.cpp

# the path of include files
INCLUDES= -I./incs -I./libs/Angel/include

# path  to sources
SRC=src

# path to libraries
LIBS=libs

# name of final executable
EXEC=ph7Museum

# compile the project
all: $(EXEC)

# build the final execuatable
$(EXEC): InitShader.o $(SRC)/ph7Main.cpp $(MODULES)
	echo "PH7: Initial makefile."
	g++ -o $(EXEC) $(INCLUDES) InitShader.o $(SRC)/ph7Main.cpp $(MODULES) $(CXXFLGS) $(GLFLGS)

# compile the init shader, the InitShader code is used as is from Angel
InitShader.o: $(LIBS)/Angel/InitShader.cpp
	g++ -c -Wall $(LIBS)/Angel/InitShader.cpp $(INCLUDES) -o InitShader.o

# remove object files
clean:
	rm *.o *$(EXEC)

