#include "Mesh.h"


Mesh::Mesh(const GeometryData& cpu_data)
: _cpu_data{cpu_data}
{    
    // RAII
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo );

    // Create the Index Buffer Object (IBO i.e. EBO)
    glGenBuffers(1, &_ibo );
}


Mesh::~Mesh()
{
    // RAII
    reset_gpu_handles();
}


Mesh::Mesh(Mesh&& other) noexcept
: _cpu_data(std::move(other._cpu_data)),
  _vao(other._vao),
  _vbo(other._vbo),
  _ibo(other._ibo)
{
    other._vao = other._vbo = other._ibo = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other) 
    {
            // reset old the cpu resources handles
            reset_gpu_handles();

            // Moves a resoruce in OpenGL is move the handle id, not copying GPU data
            _cpu_data = std::move(other._cpu_data);
            _vao = other._vao;
            _vbo = other._vbo;
            _ibo = other._ibo;

            // Leaves the other object in valid state
            other._vao = other._vbo = other._ibo = 0;
    }
    return *this;
}

void Mesh::reset_gpu_handles()
{
    if (_ibo)
        glDeleteBuffers(1, &_ibo);

    if (_vbo)
        glDeleteBuffers(1, &_vbo);

    if (_vao)
        glDeleteVertexArrays(1, &_vao);

    _vao = _vbo = _ibo = 0;
}


void Mesh::upload_to_gpu()
{
    // Selects the vao we just create
    glBindVertexArray( _vao );

    // Binds the VBO in the GPU
    glBindBuffer( GL_ARRAY_BUFFER, _vbo);

    // Upload data to GPU
    glBufferData(GL_ARRAY_BUFFER,                       
                 _cpu_data.vertices_size() * sizeof(Vertex),
                 _cpu_data.vertices().data(),
                 GL_STATIC_DRAW );                       

    // Index Buffer Object uploading

    // Binds the IBO in the GPU
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo);
    //            ^~~~~~~~~~~~~~~~~~~~~~
    //              Vertex array indices      
    // Upload and populate the vertex indices array to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,                       
                 _cpu_data.indices_size() * sizeof(GLuint),
                 _cpu_data.indices().data(),
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
    GLsizei stride = sizeof(Vertex);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, _cpu_data.position_size(), GL_FLOAT, GL_FALSE, stride, (GLvoid*) 0 );
    
    // Colors       
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, _cpu_data.color_size(), GL_FLOAT, GL_FALSE, stride, (GLvoid*)( _cpu_data.position_size() * sizeof(GLfloat) ) );


    // IMPORTANT:
    // - Attribute enable state is stored in the VAO
    // - Do NOT disable it here
    // Unbind our currently bound VAO
    glBindVertexArray(0);
}

void Mesh::draw() const
{
    // Enable our attributes
    glBindVertexArray(_vao);

    // Note:
    //  The GL_ARRAY_BUFFER and ELEMENT_ARRAY_BUFFER binding are stored in the VAO That’s why you do not need to rebind _ibo/_vbo in draw().

    // Render data
    // We need to tell to use the vertex array indices when drawing 
    glDrawElements(GL_TRIANGLES, 
                   _cpu_data.indices().size(),  // count  : The number of elements to be rendered.
                   GL_UNSIGNED_INT,                   // type   : Specifies the type of the values in indices. 
                                                      //          Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
                   (const GLvoid *)0);                // indices: Specifies an offset of the first index in the array in the 
                                                      //          data store of the buffer currently bound to the GL_ELEMENT_ARRAY_BUFFER target.
}

