#version 410 core
//       ^~~
//     OpenGL version 4.1

// It is taking-IN poistion data
   in vec4 position;   //  'position' is a vec4 containing (x, y, z, w).
// ^~ ^~~~ ^~~~~~~~~ ->  This data comes from a VBO and is associated
// |   |                 with an attribute location via a VAO.
// |   |
// |  It is a data-type that defines struct with x, y, z, w fields
// |      
// Indicates that it is an Input for this stage

void main()
{
    // The vertex shader runs once per vertex. It is responsible for computing the final position of 
    // the vertex in clip space.

    // gl_Position is a built-in output variable.
    // All built-in variables start with the 'gl_' prefix.
    gl_Position = position;

    // Additional logic could be applied here, such as transformations or offsets or just another logic.
    //
    // For ex, instead of the line above, we could have done:
    //  
    // gl_Position = vec4(position.x + 1, position.y + 3, position.z  + 1, position.w - 1);
}
