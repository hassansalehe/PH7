///////////////////////////////////////////////////////////////////////////////
//
//                   COMP 510, Computer Graphics, Spring 2016
//                              Final project
//                PH7: A virtual Museum Based on OpenGL and Glut
//
//                            (c) 2016 - Hassan & Pirah.
//            Copying without the authors consent is strictly prohibited.
//
///////////////////////////////////////////////////////////////////////////////
//
// Defines stubs for the callback functions used by OpenGL and Glut.
// Their implementations are in Init.cpp
//
///////////////////////////////////////////////////////////////////////////////

#ifndef PH7_INIT
#define PH7_INIT

#include "Museum.h"

extern Museum museum;

// function for initializing the museum
void PH7initialize();

// stub for glutDisplayFunc
void displayMuseum();

// stub for glutIdleFunc
void idleRedisplay();

void reshapeMuseum(int w, int h);

#endif
