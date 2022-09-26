#ifndef _RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_

#include <stdio.h> 

#include "glad/glad.h"

struct gl_textures {
    int size;
    int count;
    GLuint *textures;
};

struct pgt_image {
    unsigned char *image;
    int width;
    int height;
    int channels;
};

void render_texture(const char *image_path);
int render_add_texture(const char *image_path, 
                        struct gl_textures *textures);
void render_bind_texture(struct gl_textures *textures, int index);

#endif;