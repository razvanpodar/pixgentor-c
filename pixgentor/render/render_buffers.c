#include "render_buffers.h"

#include <stdio.h>

struct gl_buffers render_generate_buffers()
{
    struct gl_buffers buffers = { .vao = 0, .vbo = 0, .ebo = 0 };

    glGenVertexArrays(1, &buffers.vao);
    glGenBuffers(1, &buffers.vbo);
    glGenBuffers(1, &buffers.ebo);

    return buffers;
}

void render_bind_buffers(struct gl_buffers *buffers,
                         GLfloat vertices[], int v_size,
                         GLuint indices[], int i_size)
{
    glBindVertexArray(buffers->vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers->vbo);
    glBufferData(GL_ARRAY_BUFFER, v_size * sizeof(GL_FLOAT),
                 vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size * sizeof(GLuint),
                 indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(GLfloat) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          sizeof(GLfloat) * 5,
                          (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void render_draw(struct gl_buffers *buffers, int size)
{
    glBindVertexArray(buffers->vao);
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}