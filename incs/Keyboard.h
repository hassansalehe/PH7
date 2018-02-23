///////////////////////////////////////////////////////////////////////
//
//                   COMP 510, Computer Graphics, Spring 2016
//                              Final project
//                PH7: A virtual Museum Based on OpenGL and Glut
//
//                          (c) 2016,2017,2018 - Hassan & Pirah.
//          Copying without the authors consent is strictly prohibited.
//
///////////////////////////////////////////////////////////////////////
//
// Header for keyboard functions
//
///////////////////////////////////////////////////////////////////////
#ifndef KEYBOARD_CALLBACKS_HPP
#define KEYBOARD_CALLBACKS_HPP

#include "Init.h"

void KeyboardCallbacks(unsigned char key, int x, int y);
void KeyboardSpecialKeys( int key, int x, int y );
void MouseClickCallback( int button, int state, int x, int y );

#endif
