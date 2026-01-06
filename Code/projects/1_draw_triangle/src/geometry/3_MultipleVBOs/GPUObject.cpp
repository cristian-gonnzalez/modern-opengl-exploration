#include "GPUObject.h"



GPUObject::GPUObject(const GeometryData& cpu_data)
: _vbos(2, 0), _cpu_data{cpu_data}, _shader{"/tmp/gl/shaders/multiple_vbo"}
{    
    // RAII
    // Creates a VAO in the GPU
    glGenVertexArrays(1, &_vao);

    // Creates a new vertext buffer object (VBO) in the GPU    
    glGenBuffers(2, _vbos.data() );
}


GPUObject::~GPUObject()
{
    // RAII
    for(auto&vbo :_vbos)
        if (vbo)
            glDeleteBuffers(1, &vbo);

    if (_vao)
        glDeleteVertexArrays(1, &_vao);
}

void GPUObject::upload_to_gpu()
{
    // How do we get vertices data on our GPU? 
    //   We need to setup the VAO (Vertex Array object) and the VBO (Vertex Buffer Object)
 
    // Selects the vao we just create
    glBindVertexArray( _vao );

    // Stores actual vertex data in the VBO (GPU memory)
//           VAO (_vao)   
    //          ┌───────────────────────────────────┐  
    //          | ┌──────────────────────────────┐  |
    //          | | name      | type  | location |  |             VBO (_vbos[0])
    //          | | position  | vec3  | 0        |--|------------>[ x,y,z,  x,y,z,  x,y,z ]
    //          | | colors    | vec3  | 1        |--|---┐         VBO (_vbos[1])
    //          | └──────────────────────────────┘  |   └-------->[ r,g,b,  r,g,b,  r,g,b ]
    //          └───────────────────────────────────┘
    
    // Upload data to GPU:
    
    // positions
    glBindBuffer( GL_ARRAY_BUFFER, _vbos[0] ); 
    glBufferData( GL_ARRAY_BUFFER,                       // GLenum target : kind of buffer
                  _cpu_data.vertices.size() * sizeof(GLfloat),     // size: Specifies the size in bytes of the buffer object's new data store
                  _cpu_data.vertices.data(),
                  GL_STATIC_DRAW );                      // GLenum usage:  Specifies the expected usage pattern of the data store. 
    
    // we need to enable and point the VAO attribute o the current bound buffer
    // Note:
    //   glVertexAttribPointer records a relationship between an attribute index and the buffer currently bound to GL_ARRAY_BUFFER.
    // That's why 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, _cpu_data._attr_size, GL_FLOAT, GL_FALSE, 0, nullptr);

    
    // colors
    glBindBuffer( GL_ARRAY_BUFFER, _vbos[1] ); 
    glBufferData( GL_ARRAY_BUFFER,                       // GLenum target : kind of buffer
                  _cpu_data.colors.size() * sizeof(GLfloat),     // size: Specifies the size in bytes of the buffer object's new data store
                  _cpu_data.colors.data(),
                  GL_STATIC_DRAW );                  

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, _cpu_data._color_nums, GL_FLOAT, GL_FALSE, 0, nullptr); 


    // IMPORTANT:
    // - Attribute enable state is stored in the VAO
    // - Do NOT disable it here
    // Unbind our currently bound VAO
    glBindVertexArray(0);
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
    //glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Render data
    glDrawArrays(GL_TRIANGLES, 0, _cpu_data._num_vertex); 
    //                         ^  ^ end vertex
    //                       start vertex
}
