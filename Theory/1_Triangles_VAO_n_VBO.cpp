/** Triangles, Vertex Array Object (VAO) and Vertex Buffer Objects
 *   Modern OpenGL
 */
#include <iostream>

/*

We use OpenGL to render geometry, and the fundamental geometric primitive
used by the GPU is the triangle.

              /\
             /  \ 
            /____\

Why triangles?

  If I take one vertex and try to bend it or twist it, the rest of the triangle moves with it and remains planar.

  This property makes rasterization simple and efficient (GPUs are optimized to process triangles).
  
  Any complex surface can be approximated using triangles

  Note:
    Rasterization means converting geometric primitives into fragments (potential pixels) that can be filled on the screen.


*/
/*
Triangles:

               .             3 vertices
              / \            3 edges
             /   \           1 face
            ._____.          

Properties:
- Simple shape
- Always planar
- Predictable behavior for the GPU
*/

/*
OpenGL objects:
    We are going to use two OpenGL objects used for geometry:

            1. Vertex Buffer Object (VBO): data
            2. Vertex Array Object (VAO): how to interpret the data


1. Vertex Buffer Object (VBO)

     A VBO stores the actual vertex data in GPU memory.
     
     Each vertex may contain attributes such as:
            - position (x, y, z)
            - color (r, g, b)
            - normals
            - texture coordinates

     The VBO is just a raw array of bytes and does not know how the data is interpreted.

     Example: 

            vbo_positions = [
                x1, y1, z1,
                x2, y2, z2,
                x3, y3, z3
            ]

            vbo_interleaved = [                // interleaved positions and colors
                x1, y1, z1, r1, g1, b1,
                x2, y2, z2, r2, g2, b2,
                x3, y3, z3, r3, g3, b3
            ]

    OpenGL functions:
        glGenBuffers()
        glBindBuffer()
        glBufferData()


2. Vertex Array Object (VAO)

     A VAO does NOT store vertex data. It is how to interpret the VBO object

     So, a VAO stores the configuration (attributes) that tells OpenGL:
        - Which VBO(s) to read from
        - How vertex attributes are laid out in memory
        - Which attribute index maps to which data
        - Stride and offset information

     Example configurations:

            VAO #1:
                attribute 0 -> position (x, y, z)

            VAO #2:
                attribute 0 -> position (x, y, z)
                attribute 1 -> color    (r, g, b)

            Multiple VAOs can reference the same VBO but interpret the data differently.


*/
/*
Relationship between VAO and VBO:

    - VBOs store vertex data
    - VAOs store vertex attribute layout and references to VBOs
    - Binding a VAO restores all vertex input state
    - During rendering, OpenGL uses the active VAO to fetch vertex data
    and send it to the vertex shader

  This allows switching how vertex data is interpreted without modifying
the underlying data.
 
  Depending on the VBO object I want to access, I will activate the VAO object to manipulate them. This is how I can sort of change
how the OpenGL state machine works (how the rendering pipleinw works based on of the VBO type)
                           
*/

int main()
{
    return 0;
}