#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "pgt/render_buffers.h"
#include "pgt/render_shaders.h"
#include "pgt/render_viewport.h"
#include "pgt/render_texture.h"

#define WIDTH 640
#define HEIGHT 480

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Pixgentor", NULL, NULL);
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

    int x = 100;
    int y = 100;
    int width = 100;
    int height = 100;

    // Pixel coordinates to OpenGL coordinates
    GLfloat x_gl = ((2.0f * x) / WIDTH) - 1.0f;
    GLfloat y_gl = ((2.0f * y) / HEIGHT) - 1.0f;
    GLfloat width_gl = ((2.0f * (x + width)) / WIDTH) - 1.0f;
    GLfloat height_gl = ((2.0f * (y + height)) / HEIGHT) - 1.0f;

    printf("x_gl = %f\n", x_gl);
    printf("y_gl = %f\n", y_gl);
    printf("width_gl = %f\n", width_gl);
    printf("height_gl = %f\n", height_gl);

    // GLfloat vertices[] = {
    //      1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    //      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    //     -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    //     -1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    // };

    // GLfloat vertices[] = {
    //      0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    //      0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    //     -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    // };

    GLfloat vertices[] = {
        width_gl, height_gl, 0.0f, 1.0f, 1.0f,
        width_gl, y_gl, 0.0f, 1.0f, 0.0f,
        x_gl, y_gl, 0.0f, 0.0f, 0.0f,
        x_gl, height_gl, 0.0f, 0.0f, 1.0f
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
        .width = 200,
        .height = 200
    };

    // render_set_viewport(&viewport);

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