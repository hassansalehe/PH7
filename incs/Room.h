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
#include "Angel.h"
#include "Object.h"

typedef vec4  color4;
typedef vec4  point4;

class Room: public Object {
  private:
    // Array of rotation angles (in degrees) for each coordinate axis
    enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
    int  Axis = Yaxis;
    GLfloat  Theta[NumAxes] = { 0.0, 30.0, 0.0 };

    // Model-view and projection matrices uniform location
    GLuint  ModelView, Projection;
    
    int numVertices;
    point4 * points;
    color4 * colors;
    
    int vertexIndex;
    // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[12] = {
      point4( -0.5, -0.5,  0.5, 1.0 ),
      point4( -0.5,  0.5,  0.5, 1.0 ),
      point4(  0.5,  0.5,  0.5, 1.0 ),
      point4(  0.5, -0.5,  0.5, 1.0 ),
      point4( -0.5, -0.5, -0.5, 1.0 ),
      point4( -0.5,  0.5, -0.5, 1.0 ),
      point4(  0.5,  0.5, -0.5, 1.0 ),
      point4(  0.5, -0.5, -0.5, 1.0 ),
      point4(  -1.0,  -1.0, 1.0, 1.0 ),
      point4(  1.0,  -1.0, 1.0, 1.0 ),
      point4(  1.0,  -0.4, -1.0, 1.0 ),
      point4(  -1.0,  -0.4, -1.0, 1.0 )
    };  
      
    // RGBA olors
    color4 vertex_colors[12] = {
      color4( 0.0, 0.0, 0.0, 1.0 ),  // black
      color4( 1.0, 0.0, 0.0, 1.0 ),  // red
      color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
      color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
      color4( 1.0, 1.0, 1.0, 1.0 ),  // white
      color4( 0.0, 1.0, 1.0, 1.0 ),   // cyan
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
      color4( 0.0, 1.0, 0.0, 1.0 ),  // green
    };
    
    void quad( int a, int b, int c, int d ) {
      // Initialize colors
      colors[vertexIndex] = vertex_colors[a]; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[b]; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[c]; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[a]; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[c]; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[d]; points[vertexIndex] = vertices[d]; vertexIndex++;
    }
    
    // generate 12 triangles: 36 vertices and 36 colors
    void colorcube() {
      quad( 1, 0, 3, 2 );
      quad( 2, 3, 7, 6 );
      quad( 3, 0, 4, 7 );
      quad( 6, 5, 1, 2 );
      quad( 4, 5, 6, 7 );
      quad( 5, 4, 0, 1 );
      quad( 8, 9, 10, 11 );
    }
    
  public:
    /**
     * Initializes the vertices and colors of the empty room object.
     */
    void initialize() {
      numVertices = 42; //(7 faces)(2 triangles/face)(3 vertices/triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];
      
      // quad generates two triangles for each face and assigns colors
      //    to the vertices
      vertexIndex = 0;
      colorcube();
      
      // Create a vertex array object
      GLuint vao;
      glGenVertexArrays( 1, &vao );
      glBindVertexArray( vao );
      
      size_t points_size = sizeof(point4)*numVertices;
      size_t colors_size = sizeof(color4)*numVertices;
      
      // Create and initialize a buffer object
      GLuint buffer;
      glGenBuffers( 1, &buffer );
      glBindBuffer( GL_ARRAY_BUFFER, buffer );
      glBufferData( GL_ARRAY_BUFFER, points_size + colors_size, NULL, GL_STATIC_DRAW );
      glBufferSubData( GL_ARRAY_BUFFER, 0, points_size, points );
      glBufferSubData( GL_ARRAY_BUFFER, points_size, colors_size, colors );
      
       // Load shaders and use the resulting shader program
      GLuint program = InitShader( "RoomVshader.glsl", "RoomFshader.glsl" );
      
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

    void display( void )
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //  Generate tha model-view matrix
      const vec3 displacement( 0.0, 0.0, 0.0 );
      mat4  model_view = ( Scale(1.0, 1.0, 1.0) * Translate( displacement ) *
              RotateX( Theta[Xaxis] ) *
              RotateY( Theta[Yaxis] ) *
              RotateZ( Theta[Zaxis] ) ); 
      
      glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );

      glDrawArrays( GL_TRIANGLES, 0, numVertices );
      glutSwapBuffers();
    }
    
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
};

extern Room room;

#endif // end room