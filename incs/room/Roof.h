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
// Implements the roof of the museum
//
///////////////////////////////////////////////////////////////////////////////

#ifndef ROOF_CLASS
#define ROOF_CLASS

#include "Object.h"

class Roof: public Object {
  private:

    /**
     * Constructs one face(two triangles) of the roof sheet
     */
    void one_face( point4 lower, point4 upper, point4 third, point4 fourth ) {

      colors[vertexIndex] = blue; points[vertexIndex] = lower; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = upper; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = third; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = lower; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = third; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = fourth; vertexIndex++;
    }

    /**
     * Constructs the sheets of the roof, with
     */
    void construct_sheets(point4 lower, point4 upper) {

      float d = 0.02; // interval
      point4 third; // third vertex
      point4 fourth; // fourth vertex

      int num = 0;
      for(num = 0; num < 60; num++)
      {
        if( num % 2 ) { // is odd
          third = upper - point4(0.0, 0.0, d, 0.0);
          fourth = lower - point4(0.0, 0.0, d, 0.0);

          one_face(lower, upper, third, fourth);

          lower = fourth; upper = third;
        }
        else { // even
          third = upper - point4(0.0, -d/2, d, 0.0);
          fourth = lower - point4(0.0, -d/2, d, 0.0);
          one_face(lower, upper, third, fourth);

          lower -= point4(0.0, 0.0, 2*d, 0.0);
          upper -= point4(0.0, 0.0, 2*d, 0.0);
          one_face(fourth, third, upper, lower);
        }
      }
    }

    //(180 faces)(2 triangles/face)(3 vertices/triangle)
    void colorcube() {

      // Constructing the left roof
      point4 lower = point4( -0.6,  0.45,  0.9, 1.0 );
      point4 upper = point4(  0.0,  0.8,  0.9, 1.0 );
      construct_sheets(lower, upper); // left roof

      // Constructing the right roof
      lower = point4( 0.6,  0.45,  0.9, 1.0 );
      upper = point4(  0.0,  0.8,  0.9, 1.0 );
      construct_sheets(upper, lower); // right roof
    }

  public:
    /**
     * Initializes the vertices and colors of the empty room object.
     */
    void initialize(GLuint program) {

      // Object identifier
      object_id = 200;

      // set picking color
      isPicking = false;
      pickingColor = color4(0.0, 1.0, 0.0, 1.0); // (0,255,0)
virtual void rotateLeft( GLfloat delta ) = 0;
      numVertices = 1080; //(180 faces)(2 triangles/face)(3 vertices/triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];
      normals = new normal3[numVertices];

      // quad generates two triangles for each face and assigns colors
      //    to the vertices
      vertexIndex = 0;
      colorcube();

      // compute normals
      calculateNormals();

      shininess = 120;
      initializeDataBuffers( program );
    }

    void calculateModelViewMatrix() {
      model_view = parent_model_view;
    }


    void idle( void )
    {
      glutPostRedisplay();
    }


    // no individual rotations
    void rotateLeft(float delta) {}
    void rotateUp(float delta) {}

    void checkIfPicked( unsigned char pixel[4] ) {
      if ( pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0 ) { // Roof
        printf("Roof selected\n");
      }
    }
};

#endif // end roof
