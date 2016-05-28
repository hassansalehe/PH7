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

  GLuint object_id;
  GLuint objectID;

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
  float scaleFactor = 1.0;

  // Array of rotation angles (in degrees) for each coordinate axis
  enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
  int  Axis = Yaxis;
  GLfloat  Theta[NumAxes] = { 5.0, 0.0, 0.0 };
  GLfloat  Distance[NumAxes] = { 0.0, 0.0, 0.0 };

  color4 blue   = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
  color4 black  = color4( 0.0, 0.0, 0.0, 1.0 );  // black
  color4 red    = color4( 1.0, 0.0, 0.0, 1.0 );  // red
  color4 yellow = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
  color4 green  = color4( 0.0, 1.0, 0.0, 1.0 );  // green

public:
  virtual void initialize(GLuint program) = 0;
  void display( GLuint program )
  {
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // set up vertex arrays
    //GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    //glEnableVertexAttribArray( vPosition );
    //glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    //GLuint vColor = glGetAttribLocation( program, "vColor" );
    //glEnableVertexAttribArray( vColor );
    // glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(points_size) );

    //  Generate tha model-view matrix
    mat4 scale = Scale( scaleFactor, scaleFactor, scaleFactor );
    const vec3 displacement( Distance[Xaxis], Distance[Yaxis], Distance[Zaxis] );
    mat4  model_view = ( scale * Translate( displacement ) *
           RotateX( Theta[Xaxis] ) *
           RotateY( Theta[Yaxis] ) // *
           // RotateZ( Theta[Zaxis] )
                       );
    /* // For perspective projection
    vec3 viewer_pos = vec3( 0.0, 0.0, 2.45 );
    model_view = ( Translate( -viewer_pos ) * scale * Translate( displacement ) *
           RotateX( Theta[Xaxis] ) *
           RotateY( Theta[Yaxis] ) // *
           // RotateZ( Theta[Zaxis] )
                       );
    */


    objectID = glGetUniformLocation( program, "ObjectID" );
    glUniform1i(objectID, object_id);

    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );
    glDrawArrays( GL_TRIANGLES, 0, numVertices );


    glBindVertexArray( 0 );
    //glDisableVertexAttribArray(vPosition);
    //glDisableVertexAttribArray(vColor);
  }

  virtual void idle() = 0;
  virtual void rotateLeft( GLfloat delta ) = 0;
  virtual void rotateUp(  GLfloat delta ) = 0;

  virtual void zoomOut(GLfloat delta) {
    scaleFactor += delta;
  }


  /**
   * For zooming in the object
   */
  virtual void zoomIn(GLfloat delta) {
    scaleFactor -= delta;
  }


  /**
   * For moving toward the museum if delta > 0
   * and moving away if delta < 0
   */
  void moveForward(  GLfloat delta ) {
    printf("moving room\n");
       Distance[Zaxis] += delta;
       scaleFactor += delta;

       glutPostRedisplay();
  }


  /**
   * Resets all parameters to defult.
   */
  virtual void reset() {
    scaleFactor = 1.0;

    Theta[Xaxis] = 5.0; Theta[Yaxis] = Theta[Zaxis] = 0.0;
    Distance[Xaxis] = Distance[Yaxis] = Distance[Zaxis] = 0.0;
  }
};

#endif // end object class
