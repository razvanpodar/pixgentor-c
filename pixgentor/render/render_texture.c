#include "pgt/render_texture.h"

#include <stdio.h>

#include "STB/stb_image.h"

struct pgt_image render_load_image(const char *image_path)
{
    int width, height, channels;
    unsigned char *img = stbi_load(image_path, &width, &height, 
                                     &channels, 0);
    if (img == NULL)
    {
        printf("ERROR::IMAGE::LOADING\n");
    }

    struct pgt_image image = {
        .image = img,
        .width = width,
        .height = height,
        .channels = channels
    };

    return image;
}

int render_add_texture(const char *image_path, 
                        struct gl_textures *textures)
{
    int count = textures->count + 1;
    int index = count - 1;
    if (count >= textures->size)
        return -1;

    GLuint texture_id;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    // Set wrapping type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // Set filtering type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    struct pgt_image image = render_load_image(image_path);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0,
                 GL_LUMINANCE, GL_UNSIGNED_BYTE, image.image);
    glGenerateMipmap(GL_TEXTURE_2D);

    textures->textures[index] = texture_id;

    textures->count = count;
    return index;
}

void render_bind_texture(struct gl_textures *textures, int index)
{
    GLuint tex_id = textures->textures[index];
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, tex_id);
}
