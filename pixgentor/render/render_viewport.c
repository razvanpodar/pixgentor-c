#include "pgt/render_viewport.h"

#include "glad/glad.h"

void render_set_viewport(struct gl_viewport *viewport)
{
    glViewport(viewport->x, viewport->y, viewport->width, viewport->height);
}