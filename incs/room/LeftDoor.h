////////////////////////////////////////////////////////////////////////
//
//                   COMP 510, Computer Graphics, Spring 2016
//                              Final project
//                PH7: A virtual Museum Based on OpenGL and Glut
//
//                            (c) 2016,2017,2018 - Hassan & Pirah.
//            Copying without the authors consent is strictly prohibited.
//
////////////////////////////////////////////////////////////////////////
//
// Implements the door of the museum
//
////////////////////////////////////////////////////////////////////////

#ifndef LEFT_DOOR_CLASS
#define LEFT_DOOR_CLASS

#include "Object.h"

class LeftDoor: public Object {
  private:

    bool amISelected = false;
    float rotationAngle = 0.0;
    bool isOpen = false;

    // indices for individual rotation of parts of the door
    int handle_start_index = 0;
    int handle_end = 0;

    int door_left_start_index = 0;
    int door_left_end  = 0;
    int door_right_end = 0;

    // centre of rotation of left door
    const vec3 fp  = vec3( -0.27, 0.0, 0.81 );
    const vec3 fp2 = vec3( 0.27, 0.0, 0.81 );

    // Vertices for the left door panel
    point4 vertices[16] = {

      // front door frame outer vertices
      point4( -0.28,  0.38,  0.8, 1.0 ), // top left (A)
      point4( -0.28, -0.38,  0.8, 1.0 ), // bottom left (B)
      point4(  0.0, -0.38,  0.8, 1.0 ), // bottom right (C)
      point4(  0.0,  0.38,  0.8, 1.0 ), // top right (D)

      // front door frame middle vertices
      point4( -0.27,  0.37,  0.82, 1.0 ), // top left (E)
      point4( -0.27, -0.37,  0.82, 1.0 ), // bottom left (F)
      point4( -0.01, -0.37,  0.82, 1.0 ), // bottom right (G)
      point4( -0.01,  0.37,  0.82, 1.0 ), // top right (H)

      // front door frame inner vertices
      point4( -0.26,  0.36,  0.81, 1.0 ), // top left (I)
      point4( -0.26, -0.36,  0.81, 1.0 ), // bottom left (J)
      point4( -0.02, -0.36,  0.81, 1.0 ), // bottom right (K)
      point4( -0.02,  0.36,  0.81, 1.0 ), // top right (L)

      // front door middle separetor vertices
      point4( -0.01,  0.375,  0.81, 1.0 ), // top left (M)
      point4( -0.01, -0.375,  0.81, 1.0 ), // bottom left (N)
      point4(  0.01, -0.375,  0.81, 1.0 ), // bottom right (O)
      point4(  0.01,  0.375,  0.81, 1.0 ), // top right (P)
    };

    // RGBA olors
    color4 vertex_colors[16] = {
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

    // faces each with two triangles
    void colorcube() {

      // Constructing door frame
      quad(0, 1, 5, 4);  // left face
      quad(1, 2, 6, 5); // bottom face
      quad(2, 3, 7, 6);  // right face
      quad(0, 4, 7, 3); // top face

      // middle faces
      quad(4,  5, 9,  8);
      quad(9,  5, 6, 10);
      quad(10, 6, 7, 11);
      quad(4,  8, 11, 7);

      door_left_start_index = vertexIndex;
      // Constructing the middle separetor
      quad( 12, 13, 14, 15 ); // midle separetor

      // Constructing the left part of the door
      int start = vertexIndex;
      quad(8, 9, 13, 12);
      door_left_end = vertexIndex;

      // Constructing the right part of the door
      //quad(15, 14, 10, 11);
      door_right_end = vertexIndex;

      for (int i = start; i < vertexIndex; i++) {
        colors[i] = color4 (92/255.0, 51/255.0, 23/255.0, 1.0); // bakers chocolate
      }

      handle_start_index = vertexIndex;
      handle_end = vertexIndex;
    }

  public:
    /**
     * Initializes the vertices and colors of the empty door object.
     */
    void initialize(GLuint program) {

      // Object identifier
      object_id = 240;

      // set picking color
      isPicking = false;
      pickingColor = color4(1.0, 0.0, 1.0, 1.0); // (255,0,255)

      numVertices = 84; // (11 faces + 3)(2 triangles/face)(3 vertices/triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];
      normals = new normal3[numVertices];

      // quad generates two triangles for each face and assigns colors
      //    to the vertices
      vertexIndex = 0;
      colorcube();

      // compute normals
      calculateNormals();

      shininess = 120;

      initializeDataBuffers( program );
    }

    void calculateModelViewMatrix() {
      if (amISelected ) {
        my_model_view = Translate(fp) * RotateY(rotationAngle) * Translate(-fp);
      }
      model_view = parent_model_view * my_model_view ;
    }

    /**
     * When idle and clicked change rotation angle
     */
    void idle( void ) {
      if ( amISelected ) {
        if ( !isOpen ) rotationAngle += 0.5;
        else           rotationAngle -= 0.5;

        if (rotationAngle > 135) {
          amISelected   = false;
          rotationAngle = 0.0;
          isOpen        = true;
        } else if (rotationAngle < 0) {
          rotationAngle = 0.0;
          amISelected   = false;
          isOpen        = false;
        }
      }

      glutPostRedisplay();
    }

    // no individual rotations
    void rotateLeft(float delta) {}
    void rotateUp(float delta) {}

    void checkIfPicked( unsigned char pixel[4] ) {

      // (255,0,255)
      if ( pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 255 ) { // Door
#ifdef DEBUG
        printf("Door selected\n");
#endif
        amISelected = true;

        if ( isOpen ) { // if the door is already open
          rotationAngle = 135;
        } else {
          rotationAngle = 0;
        }
      }
   }
};

#endif // end door
