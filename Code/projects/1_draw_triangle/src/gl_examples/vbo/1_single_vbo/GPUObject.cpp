#include "GPUObject.h"



GPUObject::GPUObject(const GeometryData& cpu_data)
: _cpu_data{cpu_data}, _shader{"/tmp/gl/shaders/single_vbo"}
{    
    // How do we get this geometry data positions on our GPU? 
    // We need to setup the VAO (Vertex Array object) and the VBO (Vertex Buffer Object)


    // Vertex Array Object (VAO) creation:
    // 
    //      - Stores *how* vertex attributes are read
    //      - Does NOT store vertex data itself
    //
    //   Generate a vertex array object
    //
    // Note:
    //   We can think of the VAO as a 'wrapper around' all of the Vertex Buffer Objects, in a sense
    // that it encapsulates all VBO state that we are setting up.
    // 
    //   Thus, it is also important that we glBindVertexArray (i.e. select the VAO to use)
    glGenVertexArrays(1,        // Specifies the number of vertex array object to generate.
                      &_vao);   // OpenGL use an integer that's sort of a handler of the object
    //                 ^~~~ 
    // OpenGL maps _vao → internal VAO object

    // Vertex Buffer Object (VBO) creation:
    // 
    //      - Stores actual vertex data in GPU memory
    //    
    //   Creates a new vertext buffer object (VBO) in the GPU
    //
    // Note:
    //   We will see a glGenBuffers/glBindBuffer pattern of code often in OpenGL of creating and binding to a buffer
    // In this example, we follow RAII, so we just create the VBO in the constructor and then releases in the destructor
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
    // How do we get vertices data on our GPU? 
    //   We need to setup the VAO (Vertex Array object) and the VBO (Vertex Buffer Object)
 
    // Selects the vao we just create
    glBindVertexArray( _vao );

    // Stores actual vertex data in the VBO (GPU memory)
    
    // Bind is equivalent to 'selecting the active buffer object' that we want to work with in OpenGL
    glBindBuffer( GL_ARRAY_BUFFER,  // GLenum target,  // Defines the information the buffer will store
    //            ^~~~~~~~~~~~~~~
    //      To access Vertex attributes
                  _vbo);            // VBO id 

    // Upload data to GPU:
    //    Now, in our currently binded buffer, we populate the data from our 'vertices' (which is on the CPU)
    // onto a buffer that will be on the GPU
    
    // Store vertices into a VBO
    glBufferData(GL_ARRAY_BUFFER,                              // GLenum target : kind of buffer
                 _cpu_data.vertices.size() * sizeof(GLfloat),  // size: Specifies the size in bytes of the buffer object's new data store
                 _cpu_data.vertices.data(),
                 GL_STATIC_DRAW );                             // GLenum usage:  Specifies the expected usage pattern of the data store. 
      //         ^~~~~~~~~~~~~~~                               //   The symbolic constant must be 
      //      data will not change often                       //        GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, 
                                                               //        GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, 
                                                               //        GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY.
    
    // Note:
    //   We cannot define the VAO layout before binding VBO (glBindBuffer), since calling glVertexAttribPointer means 
    // “Read attribute data from the buffer currently bound to GL_ARRAY_BUFFER.”
    //
    //   If no buffer is bound, this becomes either: undefined behavior or an OpenGL error in core profile
    //
    //   So before setting attribute pointers (glEnableVertexAttribArray/glVertexAttribPointer), we must call glBindBuffer

    // Defines Vertex Attribute Layout.
    // 
    //  In this case, we only have one attribute ('position') since the VBO is [x y z][x y z][x y z][x y z].... This 
    // will be our attribute location 0 
    //
    //   Attribute location 0:
    //     - 3 floats per vertex (x, y, z)
    //     - tightly packed
    //
    //           VAO (_vao)  
    //          ┌───────────────────────────────────┐  
    //          | ┌──────────────────────────────┐  |
    //          | | name      | type  | location |  |             VBO (_vbo)
    //          | | position  | vec3  | 0        |--|------------>[ x,y,z, x,y,z,  x,y,z ]
    //          | └──────────────────────────────┘  |
    //          └───────────────────────────────────┘
    //    

    // Enable attribute location 0
    glEnableVertexAttribArray(0); 
    // For the specific attribute in our vertex specification, we use 'glVertexAttributePointer' to figure out
    // how we are going to move through the data
    glVertexAttribPointer(0,	         // attribute location
                                         // In the future, you will see in our vertex shader this also correspond
                                         // to (layout=0) which selects these atrrubutes
                          _cpu_data._attr_size,             // number of components,  (x, y , z)
                          GL_FLOAT,      // GLenum type
                          GL_FALSE,      // normalized?
                          0,             // stride
                                         // 0 is used when we have only one attribute
                          (GLvoid*) 0);    // offset

    // Note:
    //  If we had more attributes such as color, this would be attribute with location 1.
    //
    //  The VBO would be [x y z][r g b a][x y z][r g b a]...
    //
    //  For each attribute to define, we must call glEnableVertexAttribArray and glVertexAttribPointer 
    //  
    // glEnableVertexAttribArray(0); 
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat) , (void*) 0);
    //                                                 ^~~~~~~~~~~~~~~~~~~~
    //                                                       Stride 
    //                                     Distance (in bytes) between consecutive vertices for the SAME attribute
    //                                     “To get the next 'position', how many bytes do I jump?”
    //                                     [x y z r g b a][x y z r g b a][x y z r g b a]
    //                                      ^ position     ^ position     ^ position
    //
    // glEnableVertexAttribArray(1); 
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat) , (void*)(3 * sizeof(GLfloat)));
    //                          ^                      ^~~~~~~~~~~~~~~~~~~~           ^~~~~~~~~~~~~~~~~~~ ofsset
    //                       [r g b a]                          Stride 
    //                                     “To get the next 'color', how many bytes do I jump?”
    //                                     [x y z r g b a][x y z r g b a][x y z r g b a]
    //                                            ^ color        ^ color        ^ color
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
    // NOTE:
    //  The GL_ARRAY_BUFFER (VBO) binding is stored in the VAO That’s why you do not need to rebind _vbo in draw().
    glBindVertexArray(_vao);

    // Render data
    glDrawArrays(GL_TRIANGLES, 0, _cpu_data._num_vertex); 
    //                         ^  ^ end vertex
    //                       start vertex
}

