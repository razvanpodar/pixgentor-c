#ifndef _RENDER_VIEWPORT_H_
#define _RENDER_VIEWPORT_H_

struct gl_viewport {
    int x;
    int y;
    int width;
    int height;
};

void render_set_viewport(struct gl_viewport *viewport);

#endif;