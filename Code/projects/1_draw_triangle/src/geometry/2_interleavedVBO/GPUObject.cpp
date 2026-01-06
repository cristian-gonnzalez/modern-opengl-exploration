#include "GPUObject.h"



GPUObject::GPUObject(const GeometryData& cpu_data)
: _cpu_data{cpu_data}, _shader{"/tmp/gl/shaders/multiple_vbo"}
{    
    // RAII
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo );
}


GPUObject::~GPUObject()
{
    // RAII
    if (_vbo)
        glDeleteBuffers(1, &_vbo);

    if (_vao)
        glDeleteVertexArrays(1, &_vao);
}

void GPUObject::upload_to_gpu()
{
    // Selects the vao we just create
    glBindVertexArray( _vao );

    // Stores actual vertex data in the VBO (GPU memory)
    //           VAO (_vao)   
    //          ┌───────────────────────────────────┐  
    //          | ┌──────────────────────────────┐  |            VBO (_vbo)
    //          | | name      | type  | location |  |            [ x,y,z,r,g,b,  x,y,z,r,g,b,  x,y,z,r,g,b, ]
    //          | | position  | vec3  | 0        |--|------┐       ^     ^
    //          | | colors    | vec3  | 1        |--|---┐  └-------┘     |
    //          | └──────────────────────────────┘  |   └----------------┘
    //          └───────────────────────────────────┘

    // Binds the VBO in the GPU
    glBindBuffer( GL_ARRAY_BUFFER, _vbo);

    // Upload data to GPU
    glBufferData(GL_ARRAY_BUFFER,                       
                 _cpu_data.vertices.size() * sizeof(GLfloat),
                 _cpu_data.vertices.data(),
                 GL_STATIC_DRAW );                       
    
    // we need to enable and point the VAO attribute o the current bound buffer
    
    // Positions:
    //
    //   The stride or jump is the distance (in bytes) between consecutive vertex data for the SAME attribute. 
    // To get the next 'vertex data attribute', how many bytes do I jump?
    //
    // [ x,y,z,r,g,b,  x,y,z,r,g,b,  x,y,z,r,g,b, ]
    //   ^             ^
    //   └─────────────┘
    //      6 positions
    //
    // stride = full vertex-data size
    GLsizei stride = 6 * sizeof(GLfloat);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, _cpu_data._position_size, GL_FLOAT, GL_FALSE, stride, (GLvoid*) 0 );
    //                       ^                                      ^
    //                    (x,y,z)                                offset
    
    // Colors       
    //   Offset is 3 element and strides remains the same:
    //
    // [ x,y,z,r,g,b,  x,y,z,r,g,b,  x,y,z,r,g,b, ]
    //         ^             ^
    //         └─────────────┘
    //            6 positions

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, _cpu_data._color_size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)( 3 * sizeof(GLfloat) ) );
    //                       ^                                       ^ 
    //                      (r,g,b)                                offset  
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
    // Select the vertex buffer object we want to enable
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Render data
    glDrawArrays(GL_TRIANGLES, 0, _cpu_data._num_vertex); 
    //                         ^  ^ end vertex
    //                       start vertex
}

