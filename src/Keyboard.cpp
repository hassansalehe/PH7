#include "Keyboard.h"

void KeyboardCallbacks(unsigned char key, int x, int y){
  printf("Good key %c\n", key);
  room.display();
}

void KeyboardSpecialKeys( int key, int x, int y ) {
  
  // rotating a surface
  switch(key) {
    case GLUT_KEY_LEFT:
      if(1) { // check if nothing is rotating.
        room.rotateLeft(1);
        printf("rotating\n");
      }
      break;
    case GLUT_KEY_RIGHT:
      if(1) { // check if nothing is rotating.
        room.rotateLeft(-1);
        printf("rotating\n");
      }
      break;
  }
}