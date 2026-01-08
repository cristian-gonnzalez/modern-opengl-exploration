#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out vec3 v_vertex_color;

// Uniform variables are not initialize in the GPU. 
// NOTE:Some system allows to initilaize in the GPU.
// We can declare in both vertex/fragment shader althou it is not mandatory
// Declares a uniform variable
//^~~~~~
uniform float u_offset;
          //  ^~
          // Prefix is just a convention

void main()
{
    v_vertex_color = color;
    gl_Position = vec4(position.x, position.y + u_offset, position.z, 1.0f);
}
