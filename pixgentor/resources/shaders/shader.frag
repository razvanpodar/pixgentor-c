#version 330 core

in vec2 tex_coords;

uniform sampler2D texture0;

out vec4 color;

void main()
{
    color = texture(texture0, tex_coords);
    // color = vec4(1.0, 0.0, 0.0, 1.0);
}