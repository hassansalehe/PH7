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
// Implements the Airplane object. It performs the following.
//
// 1. reads the vertices, the colors and the face indices
// 2. puts the vertices in vertex array
// 3. puts the colors in color array
// 4. Scales the vertices and sends them to the GPU
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AIRPLANE_CLASS
#define AIRPLANE_CLASS

#include "Object.h"
#include "PLyParser.h"

class Airplane: public Object {
  float max_v = 0.0;

  private:
    void readVertices() {
      Vindex = 0;
      long nvertices, ntriangles;
      p_ply ply = ply_open("incs/antiquity/objects/airoplane.ply", NULL, 0, NULL);
      if (!ply) return; // cant open
      if (!ply_read_header(ply)) return; // cant open
      nvertices =
      ply_set_read_cb(ply, "vertex", "x", vertex_cb, NULL, X);
      ply_set_read_cb(ply, "vertex", "y", vertex_cb, NULL, Y);
      ply_set_read_cb(ply, "vertex", "z", vertex_cb, NULL, Z);

      ntriangles = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, NULL, 0);

      // cout << nvertices << " vertices, " << ntriangles << " triangles" << endl;

      numVertices = ntriangles * 3; //( times 3 vertices per triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];
      normals = new normal3[numVertices];

      r_points = points;
      r_colors = colors;
      r_vertexIndex = &vertexIndex;

      vertexIndex = 0;

      c_points = new point4[nvertices];
      c_colors = new color4[nvertices];

      if (!ply_read(ply)) {
        cerr << "Can't open airplane model file" << endl;
        return; // cant open
      }
      ply_close(ply);

      // scale the points
      float min_x = c_points[0].x;
      float max_x = c_points[0].x;

      float min_y = c_points[0].y;
      float max_y = c_points[0].y;

      float min_z = c_points[0].z;
      float max_z = c_points[0].z;

      // find the minimum and maximum for each type of
      // vertex coordinates
      for(int i = 0; i < Vindex; i++)
      {
        min_x = MIN(min_x, c_points[i].x);
        min_y = MIN(min_y, c_points[i].y);
        min_z = MIN(min_z, c_points[i].z);

        max_x = MAX(max_x, c_points[i].x);
        max_y = MAX(max_y, c_points[i].y);
        max_z = MAX(max_z, c_points[i].z);

        if(abs(c_points[i].x) > max_v )
          max_v = abs(c_points[i].x);

        if(abs(c_points[i].y) > max_v )
          max_v = abs(c_points[i].y);

        if(abs(c_points[i].z) > max_v )
          max_v = abs(c_points[i].z);
      }

      // translate according to mid-point
      float mid_x = (min_x + max_x) / 2.0;
      float mid_y = (min_z + max_y) / 2.0;
      float mid_z = (min_z + max_z) / 2.0;

      const vec3 displacement(mid_x, mid_y,  mid_z);
      float scaleF = 0.00014 ; // manually calculated
      const mat4 transform = Translate(-0.35, -0.02, 0.42) * RotateX(120.0)
          * Scale(scaleF, scaleF, scaleF) * Translate(-displacement);
      // perform transformation
      for(int i = 0; i < numVertices; i++)
        points[i] = transform * points[i];

      // internal part of the Plane
      for(int i = 0; i < 500; i++) // inner part
        colors[i] = color4(1.0, 0.5, 0.0); // gray

      for(int i = 500; i < 2000; i++) // inner part
        //khaki 	#F0E68C 	rgb(240,230,140)
        colors[i] = color4(0.9, 0.8, 0.5);


      for(int i = 2000; i < 2500; i++) // thin metal handle
         //	Orange-Brown 	#F0F8FF 	rgb(240,248,255)
        colors[i] = color4(1.0, 0.5, 0.0);

      for(int i = 2500; i < 3000; i++) // inner thin metal handle
        colors[i] = color4(0.9, 0.9, 0.5);

      for(int i = 3000; i < 3500; i++)
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] = color4(1.0, 0.5, 0.0);

      for(int i = 3500; i < 4000; i++)
         //	aliceblue 	#F0F8FF 	rgb(240,248,255)
        colors[i] =color4(0.9, 0.8, 0.5);

      // reclaim memory
      delete c_colors;
      delete c_points;
    }


  public:
    void initialize(GLuint program) {

      readVertices(); // parse vertices from file

      // calculate the normals
      calculateNormals();

      // Object identifier
      object_id = 320;

      // set picking color
      isPicking = false;
      pickingColor = color4(1.0, 1.0, 0.0, 1.0); // (255,255,0)

      shininess = 120;
      initializeDataBuffers( program );
    }


    /**
     * Calculates final model view matrix using parent's and
     * own model view matrices
     */
    void calculateModelViewMatrix() {
       model_view =parent_model_view*my_model_view;
    }


    /**
     * Rotates the plan of auto-rotation is enabled.
     */
    void idle( void )
    {
	 if(autoOnOff!=0)
     my_model_view= my_model_view*Translate(-0.35, -0.02, 0.42)*RotateY(0.5)*Translate(0.35, 0.02, -0.42);

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
      if ( pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 0 ) { // Airplane
#ifdef DEBUG
        printf("Airplane selected\n");
#endif
		my_model_view= my_model_view*Translate(-0.35, -0.02, 0.42)*RotateY(30)*Translate(0.35, 0.02, -0.42);
      }
    }
};

#endif // end airplane