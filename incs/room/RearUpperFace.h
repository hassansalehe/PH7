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
// Implements the cube of the museum
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CUBE_CLASS
#define CUBE_CLASS

#include "Object.h"
#include "Fan.h"

class Cube: public Object {
  private:
    // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[13] = {
        point4(  0.0,  0.8,  -0.8, 1.0 ), // A
        point4( -0.5,  0.5,  -0.8, 1.0 ),
        point4(  0.5,  0.5,  -0.8, 1.0 ),
        point4( -0.0866,  0.7, -0.8, 1.0 ),
        point4( -0.0866,  0.6, -0.8, 1.0 ),
        point4(  0.0,     0.55,   -0.8, 1.0 ),
        point4(  0.0866,  0.6, -0.8, 1.0 ),
        point4(  0.0866,  0.7, -0.8, 1.0 ),
        point4(  0.0,  0.75, -0.8, 1.0 ),

        // interesting things
        point4( -0.02, 0.65, -0.8, 1.0),
        point4(  0.02, 0.65, -0.8, 1.0),
        point4(  0.0,  0.75, -0.78, 1.0),
        point4(  0.0,  0.75, -0.82, 1.0),
//         point4(  0.25, 0.65, -0.8, 1.0 ),
//         point4(  0.1,  0.65, -0.8, 1.0 ), // G
//         point4( -0.15,  0.65, -0.8, 1.0 ), // H
//         point4( -0.166,  0.6, -0.8, 1.0 ), // I
    };


    // RGBA olors
    color4 vertex_colors[8] = {
      color4( 0.0, 0.0, 0.0, 1.0 ),  // black
      color4( 1.0, 0.0, 0.0, 1.0 ),  // red
      color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
      color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
      color4( 1.0, 1.0, 1.0, 1.0 ),  // white
      color4( 0.0, 1.0, 1.0, 1.0 ),/*   // cyan
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 1.0, 0.0, 1.0 ),*/  // green
    };

    void triangle( int a, int b, int c) {
      // Initialize colors
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[c]; vertexIndex++;
    }

    // generate 12 triangles: 36 vertices and 36 colors
    void colorcube() {
      triangle(1, 4, 3); // left triangle
      triangle(1, 3, 0); // right triangle
      triangle(1, 5, 4); // top triangle
      triangle(1, 2, 5);
      triangle(5, 2, 6);
      triangle(2, 7, 6);
      triangle(2, 0, 7);
      triangle(3, 8, 0);
      triangle(0, 8, 7);
      triangle(9, 10, 11);
      triangle(9, 11, 12);
    }

  public:
    /**
     * Initializes the vertices and colors of the empty cube object.
     */
    void initialize(GLuint program) {

      // Object identifier
      object_id = 100;

      // set picking color
      isPicking = false;
      pickingColor = color4(1.0, 0.0, 0.0, 1.0); // (255,0,0)

      numVertices = 66; // (21 faces)(2 triangles/face)(3 vertices/triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];
      normals = new normal3[numVertices];

      // quad generates two triangles for each face and assigns colors
      //    to the vertices
      vertexIndex = 0;
      colorcube();

      // compute normals
      calculateNormals();

      initializeDataBuffers( program );

      Object * fan = new Fan();
      appendChild(fan);
      fan->initialize( program );
    }

    void calculateModelViewMatrix() {
      model_view = parent_model_view;
    }

    void idle( void ) {
      //Theta[Axis] += 0.1;

      //if ( Theta[Axis] > 360.0 ) {
      //    Theta[Axis] -= 360.0;
      //}

      glutPostRedisplay();
    }
//     void move(){
// 	}
    void rotateLeft(float delta) {

      Theta[Yaxis] += delta;
      if ( Theta[Yaxis] > 360.0 ) {
          Theta[Yaxis] -= 360.0;
      }
      glutPostRedisplay();
    }

    void rotateUp(float delta) {

      Theta[Xaxis] += delta;
      if ( Theta[Xaxis] > 360.0 ) {
          Theta[Xaxis] -= 360.0;
      }
      glutPostRedisplay();
    }

    void checkIfPicked( unsigned char pixel[4] ) {
      if ( pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0 ) { // Room
        printf("Room selected\n");
      }
    }
};

#endif // end cube
