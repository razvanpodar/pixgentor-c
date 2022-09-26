#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "render/render_buffers.h"
#include "render/render_shaders.h"
#include "render/render_viewport.h"
#include "render/render_texture.h"

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Pixgentor", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    const int v_size = sizeof(vertices) / sizeof(vertices[0]);
    const int i_size = sizeof(indices) / sizeof(indices[0]);;

    struct gl_viewport viewport = {
        .x = 100,
        .y = 100,
        .width = 540,
        .height = 380
    };

    render_set_viewport(&viewport);

    const char *vshader_path = "../resources/shaders/shader.vert";
    const char *fshader_path = "../resources/shaders/shader.frag";
    GLuint shader = render_compile_shaders(vshader_path, fshader_path);

    const TEX_SIZE = 16;

    GLuint *tex = (GLuint*) malloc(TEX_SIZE * sizeof(GLuint)); 

    struct gl_textures textures = {
        .size = TEX_SIZE,
        .count = 0,
        .textures = tex
    };

    int index = render_add_texture("../resources/images/image.png", 
                                   &textures);
    
    render_uniform1i_shader(shader, "texture0", 0);
    render_bind_texture(&textures, index);

    struct gl_buffers rect = render_generate_buffers();
    render_bind_buffers(&rect, vertices, v_size, indices, i_size);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        render_use_shader(shader);
        render_draw(&rect, v_size);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    render_delete_shader(shader);
    glfwTerminate();

    free(tex);

    return 0;
}