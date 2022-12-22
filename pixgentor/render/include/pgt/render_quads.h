#ifndef _RENDER_QUADS_H_
#define _RENDER_QUADS_H_

#include "pgt/utils_vector2f.h"

struct quad {
    struct vector2f position;
    GLfloat width;
    GLfloat height;
};

#endif