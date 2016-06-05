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
      color4( 164/255.0, 211/255.0, 238/255.0, 1.0 ),  // green
      color4( 99/255.0, 86/255.0, 136/255.0, 1.0 ),  // red
      color4( 47/255.0, 79/255.0, 47/255.0, 1.0 ),  // yellow
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
      color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
      color4( 1.0, 1.0, 1.0, 1.0 ),  // white
      color4( 0.0, 1.0, 1.0, 1.0 ),
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

      int start = vertexIndex;
      quad( 1, 0, 3, 2 ); // front wall
      quad( 2, 3, 7, 6 ); // right wall
      quad( 4, 5, 6, 7 ); // rear
      quad( 5, 4, 0, 1 ); // left
      quad( 6, 5, 1, 2 ); // roof
      int end = vertexIndex;

      const vec3 displacement(0.0, 0.0, 0.4);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement) * points[i];
      }

      const vec3 displacement2(0.0, 0.0, 0.8);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement2) * points[i];
      }

      const vec3 displacement3(0.7, 0.0, 0.0);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement3) * points[i];
      }

      const vec3 displacement4(0.7, 0.0, 0.4);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement4) * points[i];
      }

      const vec3 displacement5(0.7, 0.0, 0.8);
      for(int i = start; i < end; i++) {
        colors[vertexIndex] = colors[i];
        points[vertexIndex++] = Translate (displacement5) * points[i];
      }

      //quad( 3, 0, 4, 7 ); // floor

      //quad( 8, 9, 10, 11 );
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

      // Create a vertex array object
      glGenVertexArrays( 1, &vao );
      glBindVertexArray( vao );

      points_size = sizeof(point4) * numVertices;
      colors_size = sizeof(color4) * numVertices;
      normals_size = sizeof(normal3) * numVertices;

      // Create and initialize a buffer object
      glGenBuffers( 1, &buffer );
      glBindBuffer( GL_ARRAY_BUFFER, buffer );
      glBufferData( GL_ARRAY_BUFFER, points_size + colors_size + normals_size, NULL, GL_STATIC_DRAW );
      glBufferSubData( GL_ARRAY_BUFFER, 0, points_size, points );
      glBufferSubData( GL_ARRAY_BUFFER, points_size, colors_size, colors );
      glBufferSubData( GL_ARRAY_BUFFER, points_size + colors_size, normals_size, normals );

      // set up vertex arrays
      size_t size = 0;
      GLuint vPosition = glGetAttribLocation( program, "vPosition" );
      glEnableVertexAttribArray( vPosition );
      glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size) );

      size += points_size;
      GLuint vColor = glGetAttribLocation( program, "vColor" );
      glEnableVertexAttribArray( vColor );
      glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size) );

      size += colors_size;
      GLuint vNormal = glGetAttribLocation( program, "vNormal" );
      glEnableVertexAttribArray( vPosition );
      glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size) );

      shininess = 120;
      glUniform1f( glGetUniformLocation(program, "Shininess"), shininess );

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


  void calculateModelViewMatrix() {
    model_view = parent_model_view;
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

    void checkIfPicked( unsigned char pixel[4] ) {
      if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255 ) { // Stand
        printf("Stand selected\n");
      }
    }
};

#endif // end Stand
