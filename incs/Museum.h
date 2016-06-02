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

// include queue
#include <queue>

#include "Object.h"
#include "Room.h"
#include "Roof.h"
#include "Stand.h"
#include "Sun.h"
#include "Skull.h"
#include "Part.h"
#include "Walkman.h"
#include "Wheel.h"
#include "Airplane.h"
#include "Lamp.h"
using namespace std;

// create the museum class
class Museum {

private:
  Object ** objects;  // pointer to hold objects
  GLuint objectCount; // total number of objects
  GLuint program;     // pointer to program

  // queue to process the object tree
  queue<Object*> objectQueue;

  // the top object in the tree
  Object* root;


  /**
   * Callback to construct the objects and the tree
   * Each new museum object is added here.
   */
  void constructObjectTree() {

    // Create objects
    Object * room    = new Room();
    Object * roof    = new Roof();
    Object * stand   = new Stand();
    Object * sun     = new  Sun();
    Object * skull   = new Skull();
    Object * walkman = new Walkman();
	Object * part = new Part();
	Object * wheel = new Wheel();
	Object * airplane = new Airplane();
	Object * lamp = new Lamp();

    // Construct tree
    room->appendChild( roof );
    room->appendChild( stand );
    room->appendChild( sun );

    stand->appendChild( skull );
    stand->appendChild( walkman );
	stand->appendChild( part );
	stand->appendChild( wheel);
	stand->appendChild( airplane);
	stand->appendChild( lamp);
    // set root to the room object
    root = room;
  }


  /**
   * Callback to initialize the tree objects
   */
  void initializeTreeNodes() {

    // put the root in the queue
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      Object * object = objectQueue.front();
      objectQueue.pop();
      object->initialize( program );
      object->pushChildrenToQueue( objectQueue );
    }
  }


  /**
   * Callback to display objects in the tree
   */
  void displayObjects() {

    Object * object;

    // put the root in the queue
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop();

      object->display( program ); // display
      object->sendModeViewToChildren();

      object->pushChildrenToQueue( objectQueue );
    }
  }


public:

  /**
   * Initializes the objects of the museum.
   * It calls functions to create the tree nodes(objects)
   */
  void initialize() {

    // Load shaders and use the resulting shader program
    program = InitShader( "MuseumVshader.glsl", "MuseumFshader.glsl" );

    objectCount = 0;
    objects = new Object*[objectCount];

    constructObjectTree();
    initializeTreeNodes();
    displayObjects();

    // set sky blue
    // Set the state variable "clear color" to clear buffer
    glClearColor(
      0.52941176470588235294,
      0.80784313725490196078,
      0.98039215686274509804, 1.0
    );
  }

  /**
   * This stub calls all display functions of the objects
   */
  void display() {
    displayObjects();
  }


  /**
   * Launches the idle functions of each object
   */
  void idle() {

    Object * object;
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop();
      object->idle(); // call idle of each object
      object->pushChildrenToQueue( objectQueue );
    }
  }


  /**
   * The reshape function
   */
  void reshape(int w, int h) {

    Object * object;
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop();
      object->reshape( w, h ); // reshape
      object->pushChildrenToQueue( objectQueue );
    }
  }

  /**
   * Propagates the rotation angle along y-axis to all the museum
   * objects.
   */
  void rotateLeft(GLfloat delta) {

	root->rotateLeft( delta );
	displayObjects();
	/*
    Object * object;
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop();
      object->rotateLeft( delta ); // rotate
      object->pushChildrenToQueue( objectQueue );
    }
    */
  }

  /**
   * Propagates the rotation angle along x-axis to all the museum
   * objects.
   */
  void rotateUp(GLfloat delta) {
    Object * object;
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop();
      object->rotateUp( delta ); // rotate
      object->pushChildrenToQueue( objectQueue );
    }
  }

  void zoomOut(GLfloat delta) {

    Object * object;
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop();
      object->zoomOut( delta ); // zoom
      object->pushChildrenToQueue( objectQueue );
    }
  }

  void zoomIn(GLfloat delta) {

    Object * object;
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop();
      object->zoomIn( delta ); // zoom
      object->pushChildrenToQueue( objectQueue );
    }
  }
  /**
   * Move the viewer in forward direction in the museum -z Direction
   */
  void moveForward(GLfloat delta) {

    Object * object;
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop();
      object->moveForward( delta ); // move
      object->pushChildrenToQueue( objectQueue );
    }
  }


  /**
   * Function for reseting the museum to its initial
   * position and orientation
   */
  void reset() {

    Object * object;
    objectQueue.push(root);

    while(! objectQueue.empty() ) {
      object = objectQueue.front();
      objectQueue.pop(); // reset
      object->reset();
      object->pushChildrenToQueue( objectQueue );
    }
  }
};

#endif // end of museum_hpp
