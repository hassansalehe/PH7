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
// Implements the Stand of the museum
//
///////////////////////////////////////////////////////////////////////////////

#ifndef STAND_CLASS
#define STAND_CLASS

#include "Object.h"

class Stand: public Object {
  private:
    // Vertices of a rectangular stand
    point4 vertices[8] = {
      point4( -0.4, -0.4, -0.3, 1.0 ),
      point4( -0.4, -0.1, -0.3, 1.0 ),
      point4( -0.3, -0.1, -0.3, 1.0 ),
      point4( -0.3, -0.4, -0.3, 1.0 ),
      point4( -0.4, -0.4, -0.4, 1.0 ),
      point4( -0.4, -0.1, -0.4, 1.0 ),
      point4( -0.3, -0.1, -0.4, 1.0 ),
      point4( -0.3, -0.4, -0.4, 1.0 )
    };

    // RGBA olors
    color4 vertex_colors[6] = {
      color4( 164/255.0, 211/255.0, 238/255.0, 1.0 ),
      color4( 99/255.0, 86/255.0, 136/255.0, 1.0 ),
      color4( 47/255.0, 79/255.0, 47/255.0, 1.0 ),
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
      color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    };

    void quad( int a, int b, int c, int d ) {

      // Initialize colors
      colors[vertexIndex] = vertex_colors[0]; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = green; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[1]; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = green; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[2]; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[5]; points[vertexIndex] = vertices[d]; vertexIndex++;
    }

    // generate 12 triangles: 36 vertices and 36 colors
    void colorcube() {

      // generate first stand
      int start = vertexIndex;
      quad( 1, 0, 3, 2 ); // front wall
      quad( 2, 3, 7, 6 ); // right wall
      quad( 4, 5, 6, 7 ); // rear
      quad( 5, 4, 0, 1 ); // left
      quad( 6, 5, 1, 2 ); // roof
      int end = vertexIndex;

      // generate second instance of the first stand
      const vec3 displacement(0.0, 0.0, 0.4);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement) * points[i];
      }

      // generate third instance of the first stand
      const vec3 displacement2(0.0, 0.0, 0.8);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement2) * points[i];
      }

      // generate fourth instance of the first stand
      const vec3 displacement3(0.7, 0.0, 0.0);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement3) * points[i];
      }

      // generate fifth instance of the first stand
      const vec3 displacement4(0.7, 0.0, 0.4);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement4) * points[i];
      }

      // generate sixth instance of the first stand
      const vec3 displacement5(0.7, 0.0, 0.8);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement5) * points[i];
      }
    }

  public:
    /**
     * Initializes the vertices and colors of the empty Stand object.
     */
    void initialize(GLuint program) {

      // Object identifier
      object_id = 210;

      // set picking color
      isPicking = false;
      pickingColor = color4(0.0, 0.0, 1.0, 1.0); // (0,0,255)

      numVertices = 180; //(30 faces)(2 triangles/face)(3 vertices/triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];
      normals = new normal3[numVertices];

      // quad generates two triangles for each face and assigns colors
      //    to the vertices
      vertexIndex = 0;
      colorcube();

      // calculate normals
      calculateNormals();

      initializeDataBuffers( program );
    }



    void calculateModelViewMatrix() {
      // use parent's model view
      model_view = parent_model_view;
    }


    /**
	 * The idle function of the Stand.
	 */
    void idle( void )
    {
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
      if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255 ) { // Stand
#ifdef DEBUG
        printf("Stand selected\n");
#endif
      }
    }
};

#endif // end Stand