#version 410 core

// We declare this variable that comes from the vertex shader
in vec3 v_vertex_color;

out vec4 color;

uniform float u_offset;

void main()
{
    color = vec4(v_vertex_color.r, v_vertex_color.g - u_offset, v_vertex_color.b, 1.0f);
}
