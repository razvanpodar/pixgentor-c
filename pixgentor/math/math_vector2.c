#include "pgt/math_vector2.h"

struct vector2f
math_add_vector2f(struct vector2f vec1, struct vector2f vec2)
{
    struct vector2f res;
    res.x = vec1.x + vec2.x;
    res.y = vec1.y + vec2.y;

    return res;
}