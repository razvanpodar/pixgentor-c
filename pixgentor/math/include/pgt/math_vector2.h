#ifndef _MATH_VECTOR2_H_
#define _MATH_VECTOR2_H_

#include "glad/glad.h"

struct vector2f {
    union {
        GLfloat x;
        GLfloat a;
        GLfloat u;
    };

    union {
        GLfloat y;
        GLfloat b;
        GLfloat v;
    };
};

struct vector2f
math_add_vector2f(struct vector2f vec1, struct vector2f vec2);

#endif