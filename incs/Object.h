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
// Implements the basic functionalities of an object.
// Each object performs the following operations.
// 1. Initialization - initializing the object vertices, colors, textures, and other attributes
// 2. Sending this information to the GPU
// 3. Displaing the object
// 4. Manipulating the object.
// 5. Its model-view and transformation matrices will be calculated using the parent's matrices.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef OBJECT_CLASS
#define OBJECT_CLASS

#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;

class Object {
protected:
  // Model-view and projection matrices uniform location
  GLuint  ModelView, Projection;

  GLuint vao;
  GLuint buffer;

  size_t points_size;
  size_t colors_size;

  int numVertices;
  point4 * points;
  color4 * colors;

  int vertexIndex;

  // Array of rotation angles (in degrees) for each coordinate axis
  enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
  int  Axis = Yaxis;
  GLfloat  Theta[NumAxes] = { -5.0, 0.0, 0.0 };

  color4 blue = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
  color4 black = color4( 0.0, 0.0, 0.0, 1.0 );  // black

public:
  virtual void initialize(GLuint program) = 0;
  virtual void display(GLuint program) = 0;
  virtual void idle() = 0;
  virtual void rotateLeft( GLfloat delta ) = 0;
  virtual void rotateUp(  GLfloat delta ) = 0;

};

#endif // end object class
