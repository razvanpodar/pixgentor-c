#include "pgt/render_shaders.h"

#include <stdio.h>
#include <stdlib.h>

static GLuint render_compile_shader(char *shader_source,
                                    GLenum shader_type)
{
    GLuint shader;

    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);

    int success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        printf("ERROR::GL::SHADER::COMPILATION_FAILED\n");
    }

    free(shader_source);

    return shader;
}

static char *render_parse_shader(const char *shader_path)
{    
    FILE *f;
    f = fopen(shader_path, "rb");

    if (f == NULL)
    {
        char *s = (char*) malloc(sizeof(char));
        *s = 's';
        return s;
    }

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *s = (char*) malloc(size + 1);
    fread(s, size, 1, f); 

    fclose(f);
    s[size] = 0;

    return s;
}

GLuint render_compile_shaders(const char *vshader_path,
                              const char *fshader_path)
{
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader;

    char *vshader_source = render_parse_shader(vshader_path);
    char *fshader_source = render_parse_shader(fshader_path);

    vertex_shader = render_compile_shader(vshader_source, GL_VERTEX_SHADER);
    fragment_shader = render_compile_shader(fshader_source,
                                            GL_FRAGMENT_SHADER);

    shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    int success;

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        printf("ERROR::GL::SHADER::LINKING_FAILED\n");
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader;
}

void render_use_shader(GLuint shader)
{
    glUseProgram(shader);
}

void render_delete_shader(GLuint shader)
{
    glDeleteProgram(shader);
}

void render_uniform1i_shader(GLuint shader, const char *name, GLint v0)
{
    GLint location = glGetUniformLocation(shader, name);
    glUniform1i(location, v0);
}
