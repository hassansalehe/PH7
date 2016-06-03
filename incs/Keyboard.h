#ifndef KEYBOARD_CALLBACKS_HPP
#define KEYBOARD_CALLBACKS_HPP

#include "Init.h"

void KeyboardCallbacks(unsigned char key, int x, int y);
void KeyboardSpecialKeys( int key, int x, int y );
void MouseClickCallback( int button, int state, int x, int y );

#endif
