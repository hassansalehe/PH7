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

#ifndef FAN_CLASS
#define FAN_CLASS

#include "Object.h"

class Fan: public Object {
  private:
    bool isSelected = false;

    // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[4] = {
        // interesting things
        point4( -0.02, 0.65, -0.8, 1.0),
        point4(  0.02, 0.65, -0.8, 1.0),
        point4(  0.01, 0.74, -0.78, 1.0),
        point4( -0.01, 0.74, -0.82, 1.0),
    };

    // RGBA olors
    color4 vertex_colors[8] = {
      color4( 1.0, 1.0, 1.0, 1.0 ),  // white
      color4( 0.0, 0.0, 0.0, 1.0 ),  // black
      color4( 1.0, 0.0, 0.0, 1.0 ),  // red
      color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
      color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
      color4( 0.0, 1.0, 1.0, 1.0 ),
    };

    void triangle( int a, int b, int c) {
      // Initialize colors
      colors[vertexIndex] = vertex_colors[a]; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[b]; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[c]; points[vertexIndex] = vertices[c]; vertexIndex++;
    }

    // generate 12 triangles: 36 vertices and 36 colors
    void colorcube() {
      triangle(0, 1, 2);
      triangle(0, 2, 3);
      int end = vertexIndex;
      for(int i = 0; i < end; i++ ) {
        colors[vertexIndex] = vertex_colors[i];
        points[vertexIndex++] = Translate(0.0, 0.65, -0.8) * RotateZ(120) * Translate(0.0, -0.65, 0.8) * points[i];
      }

      for(int i = 0; i < end; i++ ) {
        colors[vertexIndex] = vertex_colors[i];
        points[vertexIndex++] = Translate(0.0, 0.65, -0.8) * RotateZ(240) * Translate(0.0, -0.65, 0.8) * points[i];
      }
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
      pickingColor = color4(0.4, 0.0, 0.0, 1.0); // (102,0,0)

      numVertices = 18; // (3 faces)(2 triangles/face)(3 vertices/triangle)
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
    }

    void calculateModelViewMatrix() {
      model_view =parent_model_view*my_model_view;
    }

    void idle( void ) {
      if(!isSelected) {
        my_model_view= my_model_view*Translate(0.0, 0.65, -0.8)*RotateZ(10)*Translate(0.0, -0.65, 0.8);
      }
      glutPostRedisplay();
    }


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
      if ( pixel[0] == 102 && pixel[1] == 0 && pixel[2] == 0 ) { // Fan
        isSelected = !isSelected;
#ifdef DEBUG
        printf("Fan selected\n");
#endif
      }
    }
};

#endif // end fan
