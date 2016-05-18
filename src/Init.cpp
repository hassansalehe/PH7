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
//   This is file implements the initialization function of the program.
//
///////////////////////////////////////////////////////////////////////////////

#include "Init.h"

Museum museum;

void PH7initialize() {
  museum.initialize();
}

void displayMuseum() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  museum.display();

  glutSwapBuffers();
}

void idleRedisplay() {
  museum.idle();
}

void reshapeMuseum(int w, int h) {
  //museum.reshape(w, h);
}

