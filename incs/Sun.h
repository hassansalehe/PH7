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
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SUN_CLASS_H
#define SUN_CLASS_H

#include "Object.h"

class Sun: public Object {
  private:

    // Sun properties
    color4 position = color4( 2.0, 0.0, 0.0, 0.0 );
    color4 ambient = color4( 0.2, 0.2, 0.2, 1.0 );
    color4 diffuse = color4( 1.0, 1.0, 1.0, 1.0 );
    color4 specular = color4( 1.0, 1.0, 1.0, 1.0 );

    // sun  object vertices
    point4 origin = point4(  0.0,  0.0,  0.0, 1.0 );
    point4 point1 = point4(  1.0,  0.0,  0.0, 1.0 ); // x, z
    point4 point2 = point4(  0.5,  0.0,  0.866, 1.0 ); // x, z

    // Vertices of a unit cube centered at origin, sides aligned with axes
    point4 vertices[6] = {
      point4(  0.0,  0.0,  0.0, 1.0 ),
      point4(  0.0,  0.8,  0.9, 1.0 ),
      point4(  0.0,  0.8, -0.9, 1.0 ),
      point4( -0.6,  0.45, -0.9, 1.0 ),
      point4(  0.6,  0.45,  0.9, 1.0 ),
      point4(  0.6,  0.45, -0.9, 1.0 ),
    };

    // generate 240 triangles: 720 vertices and 720 colors
    void colorcube() {
	  const vec3 displacement2( -0.92, 0.92, -0.86 );
	  color4 sky = color4( 0.52941176470588235294, 0.80784313725490196078, 0.98039215686274509804, 1.0);
	  //color4 suncolor = color4(252.0/255, 212.0/255, 64.0/255);
	  float angle = 0.0;
	  for(int i = 0; i < 6; i++) {
	    colors[vertexIndex] = yellow; // suncolor
	    points[vertexIndex] =  Translate(displacement2) * RotateX( -45 ) * Scale(0.15, 0.15, 0.15) * RotateY(angle) * origin; vertexIndex++;
        colors[vertexIndex] = sky;
        points[vertexIndex] =  Translate(displacement2) * RotateX( -45 ) * Scale(0.2, 0.2, 0.2) * RotateY(angle) * point1; vertexIndex++;
        colors[vertexIndex] = sky;
        points[vertexIndex] =  Translate(displacement2) * RotateX( -45 ) * Scale(0.2, 0.2, 0.2) * RotateY(angle) * point2; vertexIndex++;

        angle += 60.0;
	  }
    }

  public:
    /**
     * Initializes the vertices and colors of the empty room object.
     */
    void initialize(GLuint program) {

      // Object identifier
      object_id = 0;

      // set picking color
      isPicking = false;
      pickingColor = color4(0.0, 0.0, 0.0, 1.0); // (0,0,0)

      numVertices = 18; //(3 faces)(2 triangles/face)(3 vertices/triangle)
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

      // Initialize shader lighting parameters for the sun
      //void sendSunProperties(GLuint program)
      glUniform4fv( glGetUniformLocation(program, "sunAmbient"), 1, ambient );
      glUniform4fv( glGetUniformLocation(program, "sunDiffuse"), 1, diffuse );
      glUniform4fv( glGetUniformLocation(program, "sunSpecular"), 1, specular );
      glUniform4fv( glGetUniformLocation(program, "sunPosition"), 1, position );

      // Enable hiddden surface removal
      glEnable( GL_DEPTH_TEST );

      // Set state variable "clear color" to clear buffer with.
      glClearColor( 1.0, 1.0, 1.0, 1.0 );
    }

    void calculateModelViewMatrix() {}

    void display( GLuint program ) {
      printf("I am cool");
      Object::display( program );
    }

    /**
     * The idle function for the sun
     */
    void idle( void )
    {
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

    }

    ~Sun() {
      delete colors;
      delete points;
    }
};

#endif // end sun
