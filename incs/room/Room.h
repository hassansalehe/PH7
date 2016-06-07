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
// Implements the room of the museum
//
///////////////////////////////////////////////////////////////////////////////

#ifndef ROOM_CLASS
#define ROOM_CLASS

#include "Object.h"

class Room: public Object {
  private:
    // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[32] = {
      // front wall
      point4( -0.5, -0.5,  0.8, 1.0 ), // bottom left
      point4( -0.5,  0.5,  0.8, 1.0 ), // top left
      point4(  0.5,  0.5,  0.8, 1.0 ), // top right
      point4(  0.5, -0.5,  0.8, 1.0 ), // bottom right

      // front door inner vertices
      point4( -0.3, -0.4,  0.8, 1.0 ), // bottom left
      point4( -0.3,  0.4,  0.8, 1.0 ), // top left
      point4(  0.3,  0.4,  0.8, 1.0 ), // top right
      point4(  0.3, -0.4,  0.8, 1.0 ), // bottom right

      // front door outer vertices
      point4( -0.3, -0.5,  0.8, 1.0 ), // bottom left
      point4( -0.3,  0.5,  0.8, 1.0 ), // top left
      point4(  0.3,  0.5,  0.8, 1.0 ), // top right
      point4(  0.3, -0.5,  0.8, 1.0 ), // bottom right

      //rear wall
      point4( -0.5,  0.5, -0.8, 1.0 ), // 12 top left
      point4(  0.5,  0.5, -0.8, 1.0 ), // 13 top right
      point4(  0.5,  0.4, -0.8, 1.0 ), // 14 top bottom right
      point4( -0.5,  0.4, -0.8, 1.0 ), // 15 top bottom left

      point4( -0.5, -0.5, -0.8, 1.0 ), // 16 bottom left
      point4( -0.5,  0.3, -0.8, 1.0 ), // 17 bottom top left
      point4(  0.5,  0.3, -0.8, 1.0 ), // 18 bottom top right
      point4(  0.5, -0.5, -0.8, 1.0 ), // 19 bottom right

      // left-side wall
      point4( -0.5,  0.3, -0.8, 1.0), // rear mid-upper
      point4( -0.5,  0.0, -0.8, 1.0), // rear mid-lower
      point4( -0.5,  0.0,  0.8, 1.0), // front mid-lower
      point4( -0.5,  0.3,  0.8, 1.0), // front mid-upper

      //left side wall middle left face
      point4( -0.5,  0.3, -0.6, 1.0), // 20
      point4( -0.5,  0.0, -0.6, 1.0), // 21

      // left side wall middle middle face
      point4( -0.5,  0.3, -0.1, 1.0), // 22
      point4( -0.5,  0.0, -0.1, 1.0), // 23
      point4( -0.5,  0.3,  0.1, 1.0), // 24
      point4( -0.5,  0.0,  0.1, 1.0), // 25

      // left side wall middle right face
      point4( -0.5,  0.3,  0.6, 1.0), // 26
      point4( -0.5,  0.0,  0.6, 1.0), // 27

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

    void quad( int a, int b, int c, int d ) {
      // Initialize colors
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[d]; vertexIndex++;
    }

    // generate 12 triangles: 36 vertices and 36 colors
    void colorcube() {

      // Constructing front wall
      quad(1, 0, 8, 9);  // left face
      quad(4, 8, 11, 7); // bottom face
      quad(10, 11, 3, 2);  // right face
      quad(9, 5, 6, 10); // top face

      // Constructing the rear wall
      quad( 12, 13, 14, 15 ); // upper face, A

      int start = vertexIndex;
      quad( 14, 18, 18, 14 ); // middle left face, B
      points[start+2].x -= 0.1;
      points[start+4].x -= 0.1;
      points[start+5].x -= 0.1;

      start = vertexIndex;
      quad( 14, 18, 18, 14 ); // middle middle left face, C
      points[start+0].x -= 0.3;
      points[start+1].x -= 0.3;
      points[start+3].x -= 0.3;

      points[start+2].x -= 0.4;
      points[start+4].x -= 0.4;
      points[start+5].x -= 0.4;

      start = vertexIndex;
      quad( 14, 18, 18, 14 ); // middle middle right face, D
      points[start+0].x -= 0.6;
      points[start+1].x -= 0.6;
      points[start+3].x -= 0.6;

      points[start+2].x -= 0.7;
      points[start+4].x -= 0.7;
      points[start+5].x -= 0.7;

      start = vertexIndex;
      quad( 15, 17, 17, 15 ); // middle middle right face, E
      points[start+0].x += 0.1;
      points[start+1].x += 0.1;
      points[start+3].x += 0.1;

      quad( 16, 17, 18, 19 ); // lower face, F

      // Constructing the left wall
      start = vertexIndex;
      quad( 12, 20, 23, 1 ); // left upper face
      quad( 20, 21, 25, 24 ); // left middle left face
      quad( 26, 27, 29, 28 ); // left middle middle face
      quad( 30, 31, 22, 23 ); // left middle right face
      quad( 21, 16, 0, 22 ); // left lower face
      int end = vertexIndex;

      // Constructing the right wall
      // It is the reflected rotation of the left wall.
      for(; start < end; start++)
      {
        colors[vertexIndex] = earth;
        points[vertexIndex] = RotateY(180.0) * points[start];
        vertexIndex++;
      }

      // Constructing the floor
      quad( 3, 0, 16, 19 ); // floor

      //quad( 6, 5, 1, 2 ); // roof
    }

  public:
    /**
     * Initializes the vertices and colors of the empty room object.
     */
    void initialize(GLuint program) {

      // Object identifier
      object_id = 100;

      // set picking color
      isPicking = false;
      pickingColor = color4(1.0, 0.0, 0.0, 1.0); // (255,0,0)

      numVertices = 126; // (21 faces)(2 triangles/face)(3 vertices/triangle)
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

    //  Generate tha model-view matrix
    mat4 scale = Scale( scaleFactor, scaleFactor, scaleFactor );
    const vec3 displacement( Distance[Xaxis], Distance[Yaxis], Distance[Zaxis] );

    model_view = ( scale * Translate( displacement ) *
                   RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] )
                   // * RotateZ( Theta[Zaxis] )
                  );

    // For perspective projection
    vec3 viewer_pos = vec3( 0.0, 0.0, 0.0 );

   // calculate model view matrix depending on the projection mode
    switch(projectionOption) {
       case HS_PERSPECTIVE:
          viewer_pos.z = 2.45;
          model_view = ( Translate( -viewer_pos ) * scale * RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) * RotateZ( Theta[Zaxis] ) );
          break;
       case HS_ORTHOGRAPHIC:
          model_view = ( scale * Translate( displacement ) * RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) /* * RotateZ( Theta[Zaxis] ) */);
          model_view = ( scale * Translate( -viewer_pos ) * RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) * RotateZ( Theta[Zaxis] ) );
          break;
    }

    // call the reshape because it re-calculates the projection matrix
    reshape(glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
  }


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
      if ( pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0 ) { // Room
#ifdef DEBUG
        printf("Room selected\n");
#endif
      }
    }
};

#endif // end room
