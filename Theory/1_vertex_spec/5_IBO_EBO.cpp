/* 

Index buffer strategy: https://wikis.khronos.org/opengl/Vertex_Specification#Index_buffers

      When drawing a quad, we need two triangle:

                        y
                    3   ^   4          Drawing in CCW order
                    *---|---*          VBO = { // First triangle
                    |\  |   |                  //   position              color          Vertex 
                    |  \|   |                  // x      y      z
          ──────────|───|───|─────────> x      -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // 0 
                    |   |\  |                   0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   // 1 
                    |   |  \|                  -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   // 2 
                    *---|---*                  // Second triangle
                    1   |   2                  //   position              color
                                               // x      y      z
                                                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   // 1 
                                                0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   // 3 
                                               -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f    // 2 
                                             };
                      
  This approach is inefficient because vertices 1 and 2 are duplicated.
These two vertices are shared between both triangles.

  To avoid this, we use an Index Buffer Object (IBO), also known as an
Element Buffer Object (EBO). This allows us to store unique vertices
once and reuse them via indices.


      VBO = { //   position              color         Vertex  (this is also the index in the array)
              // x      y      z                        
              -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // 0 
               0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   // 1 
              -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   // 2 
               0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   // 3 
            };
      IBO = { 0, 1, 2,  // first triangle            
              1, 3, 2}  // second triangle           

  The IBO references indices into the VBO and selects vertices in CCW order
when rendering the quad. This reduces duplicated data and minimizes the
amount of information sent to the GPU.

Index Buffer Object (IBO):

  An IBO is a buffer object bound to GL_ELEMENT_ARRAY_BUFFER.

        GLuint ibo{0};

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                    vertex_indices_array_bytes_size,
                    vertex_indices_array_data,
                    GL_STATIC_DRAW);

        glDeleteBuffers(1, &ibo);

Note:
    - A VBO is bound to GL_ARRAY_BUFFER
    - An IBO is bound to GL_ELEMENT_ARRAY_BUFFER
    - The GL_ELEMENT_ARRAY_BUFFER binding is stored inside the VAO

 */
