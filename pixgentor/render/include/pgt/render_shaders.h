#ifndef _RENDER_SHADERS_H_
#define _RENDER_SHADERS_H_

#include "glad/glad.h"

GLuint render_compile_shaders(const char *vshader_path,
                              const char *fshader_path);
void render_use_shader(GLuint shader);
void render_delete_shader(GLuint shader);
void render_uniform1i_shader(GLuint shader, const char *name, GLint v0);

#endif