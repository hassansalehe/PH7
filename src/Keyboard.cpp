///////////////////////////////////////////////////////////////////////
//
//                   COMP 510, Computer Graphics, Spring 2016
//                              Final project
//                PH7: A virtual Museum Based on OpenGL and Glut
//
//                            (c) 2016,017,2018 - Hassan & Pirah.
//            Copying without the authors consent is strictly prohibited.
//
///////////////////////////////////////////////////////////////////////
//
//
//
//
///////////////////////////////////////////////////////////////////////
#include "Keyboard.h"

#define hsLog printf

void KeyboardCallbacks(unsigned char key, int x, int y){

  switch( key ) {
    case 'h': // help
    case 'H':
      museum.help();
      break;
    case 'i':
    case 'I':
      museum.reset();
      break;
    case 'q': // exiting the program
    case 'Q':
      hsLog( "The program is successfully exiting.\n" );
      hsLog( "I hope you enjoyed using it.\n" );
      exit( 0 );
        break;
    case 'z':
      museum.zoomOut( 0.01 );
      break;
    case 'Z':
      museum.zoomIn( 0.01 );
      break;
    case 'f': // for moving forward / backwards
      museum.moveForward(0.004);
      break;
    case 'F':
      museum.moveForward( -0.004 );
      break;
    case 'S':
    case 's':
      museum.changeShading();
      break;
    case 'r': // gourand, modified phong, etc
    case 'R':
      museum.changeReflection();
      break;
    case 'a':
    case 'A':
      museum.toggleAuto(); // rotation of antiquities
      break;
    case 'p':
    case 'P':
      museum.changeProjection(); // toggle projection
      break;
    default:
      ;
  }
}

void KeyboardSpecialKeys( int key, int x, int y ) {

  // rotating objects
  switch(key) {
    case GLUT_KEY_LEFT:
      museum.rotateLeft( 1.0 ); // rotate left
      break;
    case GLUT_KEY_RIGHT:
      museum.rotateLeft( -1.0 ); // rotate right
      break;
    case GLUT_KEY_UP:     /* Up directional key     /\ */
      museum.rotateUp( 1.0 );
      break;
    case GLUT_KEY_DOWN:   /* Down directional key  \/  */
      museum.rotateUp( -1.0 );
      break;
    default:
      ;
  }
}

/**
 * for mouse events.
 * Primarily this implements the picking of objects
 */
void MouseClickCallback( int button, int state, int x, int y ) {

  if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // redraw the scene with defined colors to the faces of objects

    // 1. assign colors to objects
    // 2. send some info to GPU that you are rendering for picking
    museum.enablePicking();
    museum.display();

    glFlush();

    // picking process
    y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
    unsigned char pixel[4];

    // read the current pixel's color from the back buffer
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    // send the picked pixel to all scene objects
    museum.broadcastSelectedPixel( pixel );

    // needed to avoid display of the content of the back buffer when
    // some portion of the window is obscured
    museum.disablePicking();
    glutPostRedisplay();
  }
}
