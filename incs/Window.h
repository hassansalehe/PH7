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
// Implements the window of the museum
//
///////////////////////////////////////////////////////////////////////////////

#ifndef WINDOW_CLASS
#define WINDOW_CLASS

#include "Object.h"

class Window: public Object {
  private:

    mat4 initTransform;

    // indices for individual rotation of parts of the window
    int handle_start_index = 0;
    int handle_end = 0;

    int window_left_start_index = 0;
    int window_left_end = 0;
    float rotationAngle = 120.0;

    int window_right_end = 0;

    /**
     * Function for animating opening of the window
     */
    void windowAOpenAnimation() {

      if(rotationAngle > 180.0)
        return;

      // centre of rotation of left window
      const point4 fp( -0.18, 0.0, 0.0, 1.0 );

      // left left
      for(int i = window_left_start_index; i < window_left_end; i++) {
        points[i] = Translate(fp) * RotateY(rotationAngle) * Translate(-fp) * points[i];
      }

      // handle
      const point4 fp2( 0.18, 0.0, 0.0, 1.0 );
      for(int i = handle_start_index; i < handle_end; i++) {
        points[i] = Translate(fp2) * RotateY( -rotationAngle) * Translate(-fp2) * points[i];
      }

      // right window
      for(int i = window_left_end; i < window_right_end; i++) {
        points[i] = Translate(fp2) * RotateY( -rotationAngle ) * Translate(-fp2) * points[i];
      }
      rotationAngle += 5;


      //glutPostRedisplay();
      //glutTimerFunc(1, windowAOpenAnimation, p);
    }
    // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[22] = {

      // front window frame outer vertices
      point4( -0.25,  0.2,  0.0, 1.0 ), // top left (A)
      point4( -0.25, -0.2,  0.0, 1.0 ), // bottom left (B)
      point4(  0.25, -0.2,  0.0, 1.0 ), // bottom right (C)
      point4(  0.25,  0.2,  0.0, 1.0 ), // top right (D)

      // front window frame middle vertices
      point4( -0.24,  0.19,  0.02, 1.0 ), // top left (E)
      point4( -0.24, -0.19,  0.02, 1.0 ), // bottom left (F)
      point4(  0.24, -0.19,  0.02, 1.0 ), // bottom right (G)
      point4(  0.24,  0.19,  0.02, 1.0 ), // top right (H)

      // front window frame inner vertices
      point4( -0.23,  0.18,  0.01, 1.0 ), // top left (I)
      point4( -0.23, -0.18,  0.01, 1.0 ), // bottom left (J)
      point4(  0.23, -0.18,  0.01, 1.0 ), // bottom right (K)
      point4(  0.23,  0.18,  0.01, 1.0 ), // top right (L)


      // front window middle separetor vertices
      point4( -0.01,  0.18,  0.01, 1.0 ), // top left (M)
      point4( -0.01, -0.18,  0.01, 1.0 ), // bottom left (N)
      point4(  0.01, -0.18,  0.01, 1.0 ), // bottom right (O)
      point4(  0.01,  0.18,  0.01, 1.0 ), // top right (P)

      // Vertices for the handle
      point4( -0.015, 0.1,   0.02, 1.0 ), // top left (A')
      point4( -0.015, 0.095, 0.02, 1.0 ), // bottom left (B')
      point4(  0.0,   0.09, 0.015, 1.0 ), // bottom (C')

      point4(  0.05,  0.095,  0.02, 1.0 ), // bottom right (D')
      point4(  0.05,  0.1,    0.02, 1.0 ), // top right (E')
      point4(  0.0,    0.11, 0.015, 1.0 ), // top (F')
    };

    // RGBA olors
    color4 vertex_colors[22] = {
      color4( 205/255.0, 170/255.0, 125/255.0, 1.0 ),
      black, //color4( 205/255.0, 170/255.0, 125/255.0, 1.0 ), // burly wood 3
      black, //color4( 205/255.0, 170/255.0, 125/255.0, 1.0 ), // burly wood 3
      color4( 205/255.0, 170/255.0, 125/255.0, 1.0 ),
      color4( 133/255.0, 94/255.0, 66/255.0, 1.0 ), // dark wood
      color4( 133/255.0, 99/255.0, 99/255.0, 1.0 ), // light wood
      color4( 133/255.0, 99/255.0, 99/255.0, 1.0 ),
      color4( 133/255.0, 94/255.0, 66/255.0, 1.0 ), // dark wood
      color4( 133/255.0, 94/255.0, 66/255.0, 1.0 ), // dark wood
      color4( 133/255.0, 99/255.0, 99/255.0, 1.0 ),
      color4( 133/255.0, 99/255.0, 99/255.0, 1.0 ),
      color4( 133/255.0, 94/255.0, 66/255.0, 1.0 ), // dark wood
      color4( 205/255.0, 170/255.0, 125/255.0, 1.0 ),
      color4( 205/255.0, 170/255.0, 125/255.0, 1.0 ),
      black,
      black,

      // Colors for the handle
      color4(  84/255.0,  84/255.0,  84/255.0, 1.0), // Light Steel Blue
      color4(  84/255.0,  84/255.0,  84/255.0, 1.0), // Light Steel Blue
      color4( 192/255.0, 192/255.0, 192/255.0, 1.0), // silver grey
      color4( 230/255.0, 232/255.0, 250/255.0, 1.0), // silver
      color4( 230/255.0, 232/255.0, 250/255.0, 1.0), // silver
      color4( 192/255.0, 192/255.0, 192/255.0, 1.0), // silver grey

    };

    void quad( int a, int b, int c, int d ) {

      int start = vertexIndex;
      // Initialize colors
      colors[vertexIndex] = vertex_colors[a]; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[b]; points[vertexIndex] = vertices[b]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[c]; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[a]; points[vertexIndex] = vertices[a]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[c]; points[vertexIndex] = vertices[c]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[d]; points[vertexIndex] = vertices[d]; vertexIndex++;

      // creates triangles on the other part
      colors[vertexIndex] = vertex_colors[a]; points[vertexIndex] = RotateY(180) * points[start++]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[b]; points[vertexIndex] = RotateY(180) * points[start++]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[c]; points[vertexIndex] = RotateY(180) * points[start++]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[a]; points[vertexIndex] = RotateY(180) * points[start++]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[c]; points[vertexIndex] = RotateY(180) * points[start++]; vertexIndex++;
      colors[vertexIndex] = vertex_colors[d]; points[vertexIndex] = RotateY(180) * points[start++]; vertexIndex++;
    }

    // generate 12 triangles: 36 vertices and 36 colors
    void colorcube() {

      // Constructing window frame
      quad(0, 1, 5, 4);  // left face
      quad(1, 2, 6, 5); // bottom face
      quad(2, 3, 7, 6);  // right face
      quad(0, 4, 7, 3); // top face

      // middle faces
      quad(4, 5, 9, 8);
      quad(9, 5, 6, 10);
      quad(10, 6, 7, 11);
      quad(4, 8, 11, 7);

      window_left_start_index = vertexIndex;
      // Constructing the middle separetor
      quad( 12, 13, 14, 15 ); // midle separetor

      // Constructing the left part of the window
      int start = vertexIndex;
      quad(8, 9, 13, 12);
      window_left_end = vertexIndex;

      // Constructing the right part of the window
      quad(15, 14, 10, 11);
      window_right_end = vertexIndex;

      for(int i = start; i < vertexIndex; i++)
      {
        colors[i] = color4 (92/255.0, 51/255.0, 23/255.0, 1.0); // bakers chocolate
      }

      // Construct the handle
      handle_start_index = vertexIndex;
      quad(16,17, 19, 20);
      quad(17, 18, 19, 17);
      quad(16, 20, 21, 16);
      handle_end = vertexIndex;

      // apply transformations
      for(int i = 0; i < vertexIndex; i++)
      {
        points[i] = 
        //Translate(displacement) * RotateY(angle) 
        initTransform * points[i];
      }
    }

  public:

    Window(const point4 displacement, float angle) { 
      initTransform = Translate(displacement) * RotateY(angle);
    }
    
    Window(const point4 displacement, const vec3 scale) {
      
      initTransform = Translate(displacement) * Scale(scale);
    }


    /**
     * Initializes the vertices and colors of the empty window object.
     */
    void initialize(GLuint program) {

      // Object identifier
      object_id = 240;

      // set picking color
      isPicking = false;
      pickingColor = color4(1.0, 0.0, 0.0, 1.0); // (255,0,0)

      numVertices = 168; // (28 faces )(2 triangles/face)(3 vertices/triangle)
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

   void calculateModelViewMatrix() {
     model_view = parent_model_view;
  }

//     void display( GLuint program )
//     {
//       glBindVertexArray( vao );
//       glBindBuffer( GL_ARRAY_BUFFER, buffer );
//       // set up vertex arrays
//       //GLuint vPosition = glGetAttribLocation( program, "vPosition" );
//       //glEnableVertexAttribArray( vPosition );
//       //glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
//
//       //GLuint vColor = glGetAttribLocation( program, "vColor" );
//      // glEnableVertexAttribArray( vColor );
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

    ~Window() {
      delete colors;
      delete points;
    }
};

#endif // end window
