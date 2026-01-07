#include "GPUObject.h"



GPUObject::GPUObject(const GeometryData& cpu_data)
: _cpu_data{cpu_data}, _shader{"/tmp/gl/shaders/multiple_vbo"}
{    
    // RAII
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo );

    // Create the Index Buffer Object (IBO i.e. EBO)
    glGenBuffers(1, &_ibo );
}


GPUObject::~GPUObject()
{
    
    // RAII
    if (_ibo)
        glDeleteBuffers(1, &_ibo);

    if (_vbo)
        glDeleteBuffers(1, &_vbo);

    if (_vao)
        glDeleteVertexArrays(1, &_vao);
}

void GPUObject::upload_to_gpu()
{
    // Selects the vao we just create
    glBindVertexArray( _vao );

    // Binds the VBO in the GPU
    glBindBuffer( GL_ARRAY_BUFFER, _vbo);

    // Upload data to GPU
    glBufferData(GL_ARRAY_BUFFER,                       
                 _cpu_data._vertices.size() * sizeof(GLfloat),
                 _cpu_data._vertices.data(),
                 GL_STATIC_DRAW );                       

    // Index Buffer Object uploading

    // Binds the IBO in the GPU
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo);
    //            ^~~~~~~~~~~~~~~~~~~~~~
    //              Vertex array indices      
    // Upload and populate the vertex indices array to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,                       
                 _cpu_data._vertex_indices.size() * sizeof(GLuint),
                 _cpu_data._vertex_indices.data(),
                 GL_STATIC_DRAW );                       


    // we need to enable and point the VAO attribute o the current bound buffer

    // Stores actual vertex data in the VBO (GPU memory)
    //           VAO (_vao)   
    //          ┌───────────────────────────────────┐  
    //          | ┌──────────────────────────────┐  |            VBO (_vbo)
    //          | | name      | type  | location |  |            [ x,y,z,r,g,b,  x,y,z,r,g,b,  x,y,z,r,g,b, ]
    //          | | position  | vec3  | 0        |--|------┐       ^     ^
    //          | | colors    | vec3  | 1        |--|---┐  └-------┘     |
    //          | └──────────────────────────────┘  |   └----------------┘
    //          └───────────────────────────────────┘
    
    // Positions:
    GLsizei stride = 6 * sizeof(GLfloat);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, _cpu_data._position_size, GL_FLOAT, GL_FALSE, stride, (GLvoid*) 0 );
    
    // Colors       
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, _cpu_data._color_size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)( _cpu_data._position_size * sizeof(GLfloat) ) );
}

void GPUObject::create_shader()
{
    _shader.create();
}

void GPUObject::enable_shader()
{
    _shader.enable();
}

void GPUObject::draw() const
{
    // Enable our attributes
    glBindVertexArray(_vao);

    // Note:
    //  The GL_ARRAY_BUFFER and ELEMENT_ARRAY_BUFFER binding are stored in the VAO That’s why you do not need to rebind _ibo/_vbo in draw().

    // Render data
    // We need to tell to use the vertex array indices when drawing 
    glDrawElements(GL_TRIANGLES, 
                   _cpu_data._vertex_indices.size(),  // count  : The number of elements to be rendered.
                   GL_UNSIGNED_INT,                   // type   : Specifies the type of the values in indices. 
                                                      //          Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
                   (const GLvoid *)0);                // indices: Specifies an offset of the first index in the array in the 
                                                      //          data store of the buffer currently bound to the GL_ELEMENT_ARRAY_BUFFER target.
}

