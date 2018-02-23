///////////////////////////////////////////////////////////////////////
//
//                   COMP 510, Computer Graphics, Spring 2016
//                              Final project
//                PH7: A virtual Museum Based on OpenGL and Glut
//
//                            (c) 2016,2017,2018 - Hassan & Pirah.
//            Copying without the authors consent is strictly prohibited.
//
///////////////////////////////////////////////////////////////////////
//
//   This is the main file of the project. It configures OpenGL
//   and Glut for rendering
//
///////////////////////////////////////////////////////////////////////

// include the Angel's file which implements a number
// of utility functions
#include "Angel.h"

// include the initialization function
#include "Init.h"

// include the keyboard Keyboard callbacks.
#include "Keyboard.h"

/**
 * The main function. It initializes the OpenGL library and Glut.
 */
int main( int argc, char **argv ) {
  // initialize glut
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

  // initialize the GUI window size
  glutInitWindowSize( glutGet( GLUT_SCREEN_WIDTH ),
                      glutGet( GLUT_SCREEN_HEIGHT ) );

  // position the full screen window at the center
  glutInitWindowPosition( glutGet( GLUT_SCREEN_WIDTH ) / 2,
                          glutGet( GLUT_SCREEN_HEIGHT ) / 2 );

  // create GUI window
  glutCreateWindow("PH7: A Virtual Museum on OpenGL and Glut");

  glewExperimental = GL_TRUE;
  glewInit();

  // initialize OpenGL
  PH7initialize();

  // Register keyboard and mouse event functions
  glutKeyboardFunc( KeyboardCallbacks );
  glutSpecialFunc( KeyboardSpecialKeys );
  glutReshapeFunc( reshapeMuseum );
  glutMouseFunc( MouseClickCallback );
  glutIdleFunc( idleRedisplay );
  glutDisplayFunc( displayMuseum );

  glutCloseFunc( onClosingMuseum );

  // loop indefinitely
  glutMainLoop();
  return 0;
}
