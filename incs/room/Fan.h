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
// Implements the ventilating fan of the museum
//
///////////////////////////////////////////////////////////////////////////////

#ifndef FAN_CLASS
#define FAN_CLASS

#include "Object.h"

class Fan: public Object {
  private:

    // variable to start/ stop rotation
    bool isSelected = false;

    // vertices of the wing fan
    point4 vertices[4] = {
        point4( -0.02, 0.65, -0.8, 1.0),
        point4(  0.02, 0.65, -0.8, 1.0),
        point4(  0.01, 0.74, -0.78, 1.0),
        point4( -0.01, 0.74, -0.82, 1.0),
    };

    // RGBA olors
    color4 vertex_colors[4] = {
      color4( 1.0, 1.0, 1.0, 1.0 ),  // white
      color4( 0.0, 0.0, 0.0, 1.0 ),  // black
      color4( 1.0, 0.0, 0.0, 1.0 ),  // red
      color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    };

    void triangle( int a, int b, int c) {
      // Initialize colors
      colors[vertexIndex] = vertex_colors[a]; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[b]; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[c]; points[vertexIndex] = vertices[c]; vertexIndex++;
    }

    // generates faces of the fan using the vertices
    void colorcube() {
      triangle(0, 1, 2);
      triangle(0, 2, 3);
      int end = vertexIndex;

      //  generate instances of the fan wing
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

      // Object random identifier
      object_id = 7100;

      // set picking color
      isPicking = false;
      pickingColor = color4(0.4, 0.0, 0.0, 1.0); // (102,0,0)

      numVertices = 18; // (3 faces)(2 triangles/face)(3 vertices/triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];
      normals = new normal3[numVertices];

      // quad generates two triangles for each face
      //and assigns colors to the vertices
      vertexIndex = 0;
      colorcube();

      // compute normals
      calculateNormals();

      initializeDataBuffers( program );
    }

    /**
     * Calculate the model view matrix using
     * the parent model view and own transformation
     */
    void calculateModelViewMatrix() {
      model_view =parent_model_view*my_model_view;
    }


    /**
     * Rotate the fan when idle
     */
    void idle( void ) {
      if(!isSelected) {
        my_model_view= my_model_view*Translate(0.0, 0.65, -0.8)*RotateZ(10)*Translate(0.0, -0.65, 0.8);
      }
      glutPostRedisplay();
    }


    // empty, rotation depends on parent rotation
    void rotateLeft(float delta) {  }
    void rotateUp(float delta) {    }

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
