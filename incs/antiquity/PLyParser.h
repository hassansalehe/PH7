///////////////////////////////////////////////////////////////////////////////
//
//                   COMP 510, Computer Graphics, Spring 2016
//                              Final project
//                PH7: A virtual Museum Based on OpenGL and Glut
//
//                            (c) 2016 - Hassan & Pirah.
//            Copying without the authors consent is strictly prohibited.
//
//            For copyright notices of the RPLY library refer to libs/rply/LICENSE
//
///////////////////////////////////////////////////////////////////////////////
//
// Implements implements functions for parsing the ply object files
//
///////////////////////////////////////////////////////////////////////////////
#ifndef PLS_PARSER_HPP
#define PLS_PARSER_HPP

#include <stdio.h>
#include "rply.h"

#include "Object.h"

#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)

static point4 * c_points;
static color4 * c_colors;
static int Vindex = 0;
static int Cindex = 0;

static point4 * r_points;
static color4 * r_colors;
static int * r_vertexIndex;

static point4 point;
static color4 color;


enum V_TYPE{X = 1, Y = 2, Z = 3};
enum C_TYPE{RED = 702, GREEN = 800, BLUE = 900};


/**
 * Called when each vertex value is read
 */
static int vertex_cb(p_ply_argument argument) {
  long axis;
  ply_get_argument_user_data(argument, NULL, &axis);
  switch( axis ) {
    case X:
      point.x = ply_get_argument_value(argument);
      //printf("X %g ", ply_get_argument_value(argument));
      break;
    case Y:
      point.y = ply_get_argument_value(argument);
      //printf("Y %g ", ply_get_argument_value(argument));
      break;
    case Z:
      point.z = ply_get_argument_value(argument);
      //point.w = 0;
      //point = normalize(point);
      point.w = 1;
      // save the point
      c_points[Vindex] = point;
      (Vindex)++;
      //printf(" Z %g  \n", ply_get_argument_value(argument));
      break;

  //if (eol) printf("\n");
  //else printf(" ");
  }
  return 1;
}


/**
 * Called when each vertex color is read
 */
static int color_cb(p_ply_argument argument) {
  //long length, value_index;
  long color_type;
  ply_get_argument_user_data(argument, NULL, &color_type);
  switch (color_type) {
      case RED:
        color.x = ply_get_argument_value(argument) / 255.0;
        //printf(" red %g ", ply_get_argument_value(argument));
        break;
      case GREEN:
        color.y = ply_get_argument_value(argument) / 255.0;
        //printf(" green %g ", ply_get_argument_value(argument));
        break;
      case BLUE:
        color.z = ply_get_argument_value(argument) / 255.0;
        color.w = 1;

        // store color
        c_colors[Cindex] = color;
        (Cindex)++;

        //printf(" blue%g\n", ply_get_argument_value(argument));
        break;
      default:
          break;
  }
  return 1;
}


/**
 * Executed when each face index is read
 */
static int face_cb(p_ply_argument argument) {
  long length, value_index;
  ply_get_argument_property(argument, NULL, &length, &value_index);
  switch (value_index) {
      case 0:
      case 1:
      case 2:
        int idx = ply_get_argument_value(argument);
        r_points[*r_vertexIndex] = c_points[idx];
        r_colors[*r_vertexIndex] = c_colors[idx];
        (*r_vertexIndex)++;
        break;
  }
  return 1;
}

#endif // PLS_PARSER_HPP
