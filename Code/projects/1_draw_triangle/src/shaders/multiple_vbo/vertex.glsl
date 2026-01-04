#version 410 core
/*
Layout qualifier

    A 'layout' is specifying the actual vertex data. 

    You have to tell to OpenGL where is the actual data

*/

//       Atrribute 0 (position)       
//       ^~~~~~~~~~
  layout(location=0) in vec3 position;
//^~~~~~ 
//  VAO

//       Atrribute 1 (color)       
//       ^~~~~~~~~~
layout(location=1) in vec3 color;

// We want to send out the colors to the next stage of the pipeline.
//
// Note: 
//   What is going to do with ths line is pass from the vertex shader into the fragment shader
// Now, we must declare a 'in vec3 v_vertex_color' in the fragemnt shader 
out vec3 v_vertex_color;
//       ^~
//     by convention we use v_ to specified it was created in the vertex spoecification stage

void main()
{
    v_vertex_color = color;
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
}
