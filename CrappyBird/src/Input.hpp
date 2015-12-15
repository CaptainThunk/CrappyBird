//
//  Input.hpp
//  CrappyBird
//
//  Created by Dean Becker on 14/12/2015.
//  Copyright © 2015 Dean Becker. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include "gl_headers.h"

#include <stdio.h>

void key_callback(GLFWwindow* window,
                         int key,
                         int scancode,
                         int action,
                         int mods);

bool isKeyDown(int key);

#endif /* Input_hpp */
