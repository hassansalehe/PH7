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
    // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[8] = {
      point4( -0.4, -0.4, -0.3, 1.0 ),
      point4( -0.4, -0.1, -0.3, 1.0 ),
      point4( -0.3, -0.1, -0.3, 1.0 ),
      point4( -0.3, -0.4, -0.3, 1.0 ),
      point4( -0.4, -0.4, -0.4, 1.0 ),
      point4( -0.4, -0.1, -0.4, 1.0 ),
      point4( -0.3, -0.1, -0.4, 1.0 ),
      point4( -0.3, -0.4, -0.4, 1.0 )/*,
      point4(  -1.0,  -1.0, 1.0, 1.0 ),
      point4(  1.0,  -1.0, 1.0, 1.0 ),
      point4(  1.0,  -0.4, -1.0, 1.0 ),
      point4(  -1.0,  -0.4, -1.0, 1.0 )*/
    };

    // RGBA olors
    color4 vertex_colors[8] = {
      color4( 0.0, 0.0, 0.0, 1.0 ),  // green
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
      colors[vertexIndex] = green; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = green; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = green; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = green; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = green; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = green; points[vertexIndex] = vertices[d]; vertexIndex++;
    }

    // generate 12 triangles: 36 vertices and 36 colors
    void colorcube() {

      int start = vertexIndex;
      quad( 1, 0, 3, 2 ); // front wall
      quad( 2, 3, 7, 6 ); // right wall
      quad( 4, 5, 6, 7 ); // rear
      quad( 5, 4, 0, 1 ); // left
      quad( 6, 5, 1, 2 ); // roof
      int end = vertexIndex;

      const vec3 displacement(0.0, 0.0, 0.4);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = green; points[vertexIndex] = Translate (displacement) * points[i]; vertexIndex++;
      }

      const vec3 displacement2(0.0, 0.0, 0.8);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = green; points[vertexIndex] = Translate (displacement2) * points[i]; vertexIndex++;
      }

      const vec3 displacement3(0.7, 0.0, 0.0);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = green; points[vertexIndex] = Translate (displacement3) * points[i]; vertexIndex++;
      }

      const vec3 displacement4(0.7, 0.0, 0.4);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = green; points[vertexIndex] = Translate (displacement4) * points[i]; vertexIndex++;
      }

      const vec3 displacement5(0.7, 0.0, 0.8);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = green; points[vertexIndex] = Translate (displacement5) * points[i]; vertexIndex++;
      }

      //quad( 3, 0, 4, 7 ); // floor

      //quad( 8, 9, 10, 11 );
    }

  public:
    /**
     * Initializes the vertices and colors of the empty Stand object.
     */
    void initialize(GLuint program) {
      numVertices = 180; //(30 faces)(2 triangles/face)(3 vertices/triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];

      // quad generates two triangles for each face and assigns colors
      //    to the vertices
      vertexIndex = 0;
      colorcube();

      // Create a vertex array object
      glGenVertexArrays( 1, &vao );
      glBindVertexArray( vao );

      points_size = sizeof(point4)*numVertices;
      colors_size = sizeof(color4)*numVertices;

      // Create and initialize a buffer object
      glGenBuffers( 1, &buffer );
      glBindBuffer( GL_ARRAY_BUFFER, buffer );
      glBufferData( GL_ARRAY_BUFFER, points_size + colors_size, NULL, GL_STATIC_DRAW );
      glBufferSubData( GL_ARRAY_BUFFER, 0, points_size, points );
      glBufferSubData( GL_ARRAY_BUFFER, points_size, colors_size, colors );

      // set up vertex arrays
      GLuint vPosition = glGetAttribLocation( program, "vPosition" );
      glEnableVertexAttribArray( vPosition );
      glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

      GLuint vColor = glGetAttribLocation( program, "vColor" );
      glEnableVertexAttribArray( vColor );
      glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(points_size) );

      // Set current program object
      glUseProgram( program );

      // Retrieve transformation uniform variable locations
      ModelView = glGetUniformLocation( program, "ModelView" );
      Projection = glGetUniformLocation( program, "Projection" );

      // Set projection matrix
      mat4  projection = Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
      //projection = Perspective( 45.0, 1.0, 0.5, 3.0 );
      glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );

      // Enable hiddden surface removal
      glEnable( GL_DEPTH_TEST );

      // Set state variable "clear color" to clear buffer with.
      glClearColor( 1.0, 1.0, 1.0, 1.0 );
    }

    /**
	 * The idle function of the Stand.
	 */
    void idle( void )
    {
      //Theta[Axis] += 0.1;

      //if ( Theta[Axis] > 360.0 ) {
      //    Theta[Axis] -= 360.0;
      //}

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

    ~Stand() {
      delete colors;
      delete points;
    }
};

#endif // end Stand
