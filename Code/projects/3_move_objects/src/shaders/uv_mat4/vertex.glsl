#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out vec3 v_vertex_color;

uniform mat4 u_model_matrix;

void main()
{
    v_vertex_color = color;

    vec4 new_position = u_model_matrix * vec4( position, 1.0f );
    gl_Position = vec4(new_position.x, new_position.y, new_position.z, 1.0f);
}
