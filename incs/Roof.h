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
    // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[6] = {
      point4( -0.6,  0.45,  0.9, 1.0 ),
      point4(  0.0,  0.8,  0.9, 1.0 ),
      point4(  0.0,  0.8, -0.9, 1.0 ),
      point4( -0.6,  0.45, -0.9, 1.0 ),
      point4(  0.6,  0.45,  0.9, 1.0 ),
      point4(  0.6,  0.45, -0.9, 1.0 ),
    };

    void quad( int a, int b, int c, int d ) {
      // Initialize colors
      colors[vertexIndex] = blue; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = blue; points[vertexIndex] = vertices[d]; vertexIndex++;
    }

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

    // generate 240 triangles: 720 vertices and 720 colors
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

      // Create a vertex array object
      glGenVertexArrays( 1, &vao );
      glBindVertexArray( vao );

      points_size =  sizeof(point4) * numVertices;
      colors_size =  sizeof(color4) * numVertices;
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

      glUniform1f( glGetUniformLocation(program, "Shininess"), 15 );
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

//     void display( GLuint program )
//     {
//       glBindVertexArray( vao );
//       glBindBuffer( GL_ARRAY_BUFFER, buffer );
//
//       // set up vertex arrays
//       //GLuint vPosition = glGetAttribLocation( program, "vPosition" );
//       //glEnableVertexAttribArray( vPosition );
//       //glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
//
//       //GLuint vColor = glGetAttribLocation( program, "vColor" );
//       //glEnableVertexAttribArray( vColor );
//      // glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(points_size) );
//
//       //  Generate tha model-view matrix
//       const vec3 displacement( 0.0, 0.0, 0.0 );
//       model_view = ( Scale(1.0, 1.0, 1.0) * Translate( displacement ) *
//               RotateX( Theta[Xaxis] ) *
//               RotateY( Theta[Yaxis] ) // *
//              // RotateZ( Theta[Zaxis] )
//                          );
//
//       glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );
//       glDrawArrays( GL_TRIANGLES, 0, numVertices );
//
//       glBindVertexArray( 0 );
//       //glDisableVertexAttribArray(vPosition);
//       //glDisableVertexAttribArray(vColor);
//     }

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
      if ( pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0 ) { // Roof
        printf("Roof selected\n");
      }
    }

    ~Roof() {
      delete colors;
      delete points;
    }
};

#endif // end roof
