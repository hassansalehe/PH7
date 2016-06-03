#include "Keyboard.h"

#define hsLog printf

void KeyboardCallbacks(unsigned char key, int x, int y){

  switch( key ) {
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
      museum.zoomOut(0.01);
      break;
    case 'Z':
      museum.zoomIn(0.01);
      break;
    case 'f': // for moving forward/  backwards
      museum.moveForward(0.004);
      break;
    case 'F':
      museum.moveForward(-0.004);
      break;

    case 'S':
    case 's':
      museum.changeShading();
      break;
    case 'r':
    case 'R':
      museum.changeReflection();
      break;

  }
}

void KeyboardSpecialKeys( int key, int x, int y ) {

  // rotating objects
  switch(key) {
    case GLUT_KEY_LEFT:
      if(1) { // check if nothing is rotating.
        museum.rotateLeft(1.0);
      }
      break;
    case GLUT_KEY_RIGHT:
      if(1) { // check if nothing is rotating.
        museum.rotateLeft(-1.0);
        printf("rotating\n");
      }
      break;
    case GLUT_KEY_UP:     /* Up directional key     /\ */
      museum.rotateUp(1.0);
      break;

    case GLUT_KEY_DOWN:   /* Down directional key  \/  */
      museum.rotateUp(-1.0);
      break;
  }
}

/**
 * for mouse events.
 * Primarily this implements the picking of objects
 */
void MouseClickCallback( int button, int state, int x, int y ) {

  if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //1. redraw the scene with defined colors to the faces of the
      //   large cube.

      // send some info to GPU that you are rendering for picking
      // Assign colors to objects
      // "originalRubiksCube".drawRubiksCube();
      museum.enablePicking();
      museum.display();

      glFlush();

      //picking process

      y = glutGet( GLUT_WINDOW_HEIGHT ) - y;

      unsigned char pixel[4];

      // read the current pixel's color from the back buffer
      glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

      if ( pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0 ) { // Room
        printf("Room selected\n");
      }
      else if ( pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0 ) { // Roof
        printf("Roof selected\n");
      }
      else if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255 ) { // Stand
        printf("Stand selected\n");
      }
      else if ( pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 0 ) { // Airplane
        printf("Airplane selected\n");
      }
      else if ( pixel[0] == 0 && pixel[1] == 51 && pixel[2] == 0 ) { // Lamp
        printf("Lamp selected\n");
      }
      else if ( pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 51 ) { // Part
        printf("Part selected\n");
      }
      else if ( pixel[0] == 51 && pixel[1] == 51 && pixel[2] == 0 ) { // Skull
        printf("Skull selected\n");
      }
      else if ( pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255 ) { // Walkman
        printf("Walkman selected\n");
      }
      else if ( pixel[0] == 51 && pixel[1] == 0 && pixel[2] == 0 ) { // Wheel
        printf("Wheel selected\n");
      }
      //else if(pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0)
      //  printf("You clicked on edges. Please click on colored cubes.\n");

      //needed to avoid display of the content of the back buffer when
      //some portion of the window is obscured
      museum.disablePicking();
      glutPostRedisplay();
  }
}
