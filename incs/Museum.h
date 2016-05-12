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
// This header file holds all the museum objects in form of a tree.
// Moreover, it contains all necessary functions to manipulate these objects.
// See Init.cpp for how the "Museum" class is used.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MUSEUM_HPP
#define MUSEUM_HPP

#include "Object.h"
#include "Room.h"
#include "Roof.h"

// create the museum class
class Museum {

private:
  Object ** objects;  // pointer to hold objects
  GLuint objectCount; // total number of objects
  GLuint program;     // pointer to program

public:

  /**
   * Initializes the objects of the museum.
   * Each new museum object is added here.
   */
  void initialize() {

  // Load shaders and use the resulting shader program
  program = InitShader( "MuseumVshader.glsl", "MuseumFshader.glsl" );

  objectCount = 2;
  objects = new Object*[objectCount];

  objects[0] = new Room();
  objects[1] = new Roof();

  // initialize the objects
  for(GLuint i = 0; i < objectCount; i++)
    objects[i]->initialize(program);

  // display the objects
  for(GLuint i = 0; i < objectCount; i++)
    objects[i]->display(program);
  }


  /**
   * This stub calls all display functions of the objects
   */
  void display() {

    // display the objects
    for(GLuint i = 0; i < objectCount; i++)
      objects[i]->display(program);
  }


  /**
   * Launches the idle functions of each object
   */
  void idle() {
    for(GLuint i = 0; i < objectCount; i++)
      objects[i]->idle();
  }

  void reshape(int w, int h){

    for(GLuint i = 0; i < objectCount; i++)
      objects[i]->reshape(w, h);
  }


  /**
   * Propagates the rotation angle along y-axis to all the museum
   * objects.
   */
  void rotateLeft(GLfloat delta) {
    for(GLuint i = 0; i < objectCount; i++)
      objects[i]->rotateLeft(delta);
  }

  /**
   * Propagates the rotation angle along x-axis to all the museum
   * objects.
   */
  void rotateUp(GLfloat delta) {
    for(GLuint i = 0; i < objectCount; i++)
      objects[i]->rotateUp(delta);
  }

  void zoomOut(GLfloat delta) {
    for(GLuint i = 0; i < objectCount; i++)
      objects[i]->zoomOut(delta);
  }

  void zoomIn(GLfloat delta) {
    for(GLuint i = 0; i < objectCount; i++)
      objects[i]->zoomIn(delta);
  }
};

#endif // end of museum_hpp
