#ifndef _RENDER_BUFFERS_H_
#define _RENDER_BUFFERS_H_

#include "glad/glad.h"

struct gl_buffers {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};

struct gl_buffers render_generate_buffers();
void render_bind_buffers(struct gl_buffers *buffers,
                         GLfloat vertices[], int v_size,
                         GLuint indices[], int i_size);
void render_draw(struct gl_buffers *buffers, int size);

#endif