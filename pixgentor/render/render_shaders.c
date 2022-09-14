#include <stdio.h>

#include "render_shaders.h"

static char *render_parse_shader(const char *shader_path);
static GLuint render_compile_shader(const char *shader_source, GLenum shader_type);

GLuint render_compile_shaders(const char *vshader_path,
                            const char *fshader_path)
{
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader;

    // char *vshader_source = render_parse_shader(vshader_path);
    // char *fshader_source = render_parse_shader(fshader_path);

    const char *vshader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char *fshader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

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

static GLuint render_compile_shader(const char *shader_source, GLenum shader_type)
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

    // free(shader_source);

    return shader;
}

static char *render_parse_shader(const char *shader_path)
{    
    FILE *f;
    f = fopen(shader_path, "rb");

    if (f == NULL)
    {
        char *s = (char*) malloc(sizeof(char));
        // *s = 's';
        // printf("%s\n", *s);
        return s;
    }

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *s = (char) malloc(size + 1);
    fread(s, size, 1, f); 

    fclose(f);
    s[size] = 0;

    return s;
}
