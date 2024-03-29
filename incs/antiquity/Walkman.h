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
// Implements the Walkman object
//
// read the vertices
// read the colors
// read the face indices
// put the vertices in vertex array
// put the colors in color array
// Scale the vertices, send them to the GPU
//
////////////////////////////////////////////////////////////////////////

#ifndef WALKMAN_CLASS
#define WALKMAN_CLASS

#include "Object.h"
#include "PLyParser.h"

class Walkman: public Object {

  private:

    /**
     * Reads vertices from Wheel.ply file
     */
    void readVertices() {

      Vindex = 0;
      long nvertices, ntriangles;
      p_ply ply = ply_open(
          "incs/antiquity/objects/walkman.ply", NULL, 0, NULL);
      if (!ply) return; // cant open
      if (!ply_read_header(ply)) return; // cant open
      nvertices =
      ply_set_read_cb(ply, "vertex", "x", vertex_cb, NULL, X);
      ply_set_read_cb(ply, "vertex", "y", vertex_cb, NULL, Y);
      ply_set_read_cb(ply, "vertex", "z", vertex_cb, NULL, Z);

      ntriangles = ply_set_read_cb(
          ply, "face", "vertex_indices", face_cb, NULL, 0);
      //printf("%ld\n%ld\n", nvertices, ntriangles);

      numVertices = ntriangles * 3; // (3 vertices/triangle)
      points      = new point4[numVertices];
      colors      = new color4[numVertices];
      normals     = new normal3[numVertices];

      r_points      = points;
      r_colors      = colors;
      r_vertexIndex = &vertexIndex;
      vertexIndex   = 0;

      c_points = new point4[nvertices];
      c_colors = new color4[nvertices];

      if (!ply_read(ply)) return; // cant open
      ply_close(ply);

      // scale the points
      float min_x = c_points[0].x;
      float max_x = c_points[0].x;

      float min_y = c_points[0].y;
      float max_y = c_points[0].y;

      float min_z = c_points[0].z;
      float max_z = c_points[0].z;

      for (int i = 0; i < Vindex; i++) {
        min_x = MIN(min_x, c_points[i].x);
        min_y = MIN(min_y, c_points[i].y);
        min_z = MIN(min_z, c_points[i].z);

        max_x = MAX(max_x, c_points[i].x);
        max_y = MAX(max_y, c_points[i].y);
        max_z = MAX(max_z, c_points[i].z);
      }

      // translate according to mid-point
      float mid_x = (min_x + max_x) / 2.0;
      float mid_y = (min_z + max_y) / 2.0;
      float mid_z = (min_z + max_z) / 2.0;

       const vec3 displacement(mid_x, mid_y,  mid_z);
       float scaleF = 0.0004 ; // manually calculated
      for (int i = 0; i < numVertices; i++) {
        points[i] = Translate(0.35, 0.0, -0.36)
                    * RotateY(-90.0)
                    * Scale(scaleF, scaleF, scaleF)
                    * Translate(-displacement)
                    * points[i];
      }

      // internal part of the walkman
      for (int i = 0; i < 1000; i++) {// inner part
        colors[i] = color4(0.5, 0.5, 0.5); // gray
      }
      for (int i = 1000; i < 2000; i++) {// inner part
        //khaki 	#F0E68C 	rgb(240,230,140)
        colors[i] = color4(0.9375, 0.8984375, 0.546875);
      }
      for (int i = 2000; i < 2500; i++) {// thin metal handle
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = color4(0.9375, 0.96875, 1.0);
      }

      for (int i = 2500; i < 3500; i++) {// inner thin metal handle
        colors[i] = black;
      }

      for (int i = 3500; i < 3600; i++) {
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = red;
      }

      for (int i = 3600; i < 3700; i++) {
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = green;
      }

      for (int i = 3700; i < 3870; i++) {// other part of earphone
        //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = black;
      }

      for (int i = 3870; i < 3978; i++) {// other part of earphone
        //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = red;
      }

      for (int i = 3978; i < 4080; i++) {// other part of earphone
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = green;
      }
      for (int i = 4080; i < 4650; i++) {// other part of earphone
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = black;
      }

      for (int i = 4650; i < 7800; i++) {// buttons
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = color4(1.0, 0.75, 0.00);
      }
      for (int i = 7800; i < 9700; i++) {// buttons
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = color4(0.75, 0.75, 0.75); // silver front
      }
      for (int i = 9700; i < 9970; i++) {// other part of the wman
        colors[i] = color4(0.5, 0.5, 0.5);
      }

      for (int i = 9970; i < 12000; i++) {// buttons
        colors[i] = color4(0.75, 0.75, 0.75); // silver front
      }
      // internal part of the walkman
      for (int i = 12000; i < numVertices; i++) {// inner part
        colors[i] = color4(0.5, 0.5, 0.5); // gray
      }

      // reclaim memory
      delete c_colors;
      delete c_points;
    }

  public:

    /**
     * initializes data and sends to GPU
     */
    void initialize(GLuint program) {

      readVertices();

      // calculate normals
      calculateNormals();

      // Object identifier
      object_id = 360;

      // set picking color
      isPicking = false;
      pickingColor = color4(1.0, 1.0, 1.0, 1.0); // (255,255,255)

      shininess = 120;

      initializeDataBuffers( program );
    }

    void calculateModelViewMatrix() {
       model_view =parent_model_view*my_model_view;
    }

    void idle( void )
    {
	  if (autoOnOff!=0)
      my_model_view= my_model_view*Translate(0.35, 0.0, -0.36)*RotateY(0.5)*Translate(-0.35, 0.0, 0.36);

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
      if ( pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255 ) { // Walkman
#ifdef DEBUG
        printf("Walkman selected\n");
#endif
		my_model_view= my_model_view*Translate(0.35, 0.0, -0.36)*RotateY(30)*Translate(-0.35, 0.0, 0.36);
      }
    }
};

#endif // end walkman
