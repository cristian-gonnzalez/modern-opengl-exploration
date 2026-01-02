#version 410 core
//       ^~~
//    OpenGL version 4.1

//  It is taking-OUT color data
  out vec4 color;   //   'color' represents the final color of the fragment
//^~ ^~~~              (r, g, b, a) that will be written to the framebuffer,
// |   |               assuming it is not discarded later. 
// |  It is a struct with r, g, b, a fields
// |      
// Indicates that it is the output variable of the fragment shader


void main()
{
    // The fragment shader runs once per fragment (a fragment is a potential pixel).

    // Set a constant color for every fragment: orange
    //           r    g    b    a
    //           ^~~  ^~~  ^~~  ^~~ 
    color = vec4(1.0, 0.5, 0.0, 1.0);

    // More complex lighting or texturing logic
    // could be applied here.
}
