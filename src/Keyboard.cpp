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
