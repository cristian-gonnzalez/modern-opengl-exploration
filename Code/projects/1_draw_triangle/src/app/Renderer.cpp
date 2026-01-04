#include "Renderer.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
 
class renderer_error : public std::runtime_error
{
    public:
        explicit renderer_error(const std::string& msg)
        : std::runtime_error(msg) 
        {}
};

Renderer::~Renderer()
{
    if (_shader_program)
        glDeleteProgram(_shader_program);

    if (_vbo)
        glDeleteBuffers(1, &_vbo);

    if (_vao)
        glDeleteVertexArrays(1, &_vao);
}

// Step 1: Geometry specification (CPU → GPU)
// 
// Goal:
// - Upload vertex data to GPU memory
// - Describe how that data should be interpreted
// 
// Pipeline stage:
// - Vertex Specification (before vertex shader)
void Renderer::setup_geometry(GeometryLayout layout)
{
    // Lives on the CPU
    //    GLfloat is defined across different architectures, they will be more
    //  uniform 
    //                ^~~~~~~
    const std::vector<GLfloat> vertices{ // x      y      z
                                           -0.8f, -0.8f, 0.0f,  // Vertex 1 (Left)
                                            0.8f, -0.8f, 0.0f,  // Vertex 2 (Right)
                                            0.0f,  0.8f, 0.0f   // Vertex 3 (Top)
                                        };

    const std::vector<GLfloat> colors{ //    r      g      b
                                            1.0f,  0.0f, 0.0f,  // Vertex 1 (Left)  red
                                            0.0f,  1.0f, 0.0f,  // Vertex 2 (Right) green 
                                            0.0f,  0.0f, 1.0f   // Vertex 3 (Top)   blue
                                        };
    
    const std::vector<GLfloat> vertices_n_colors{ // x      y      z
                                           -0.8f, -0.8f, 0.0f,  // Vertex 1 (Left)
                                            1.0f,  0.0f, 0.0f,  //           color ->  red
                                            0.8f, -0.8f, 0.0f,  // Vertex 2 (Right)
                                            0.0f,  1.0f, 0.0f,  //           color -> green 
                                            0.0f,  0.8f, 0.0f,  // Vertex 3 (Top)
                                            0.0f,  0.0f, 1.0f   //           color ->   blue
                                        };


    // How do we get these vertex positions on our GPU? 
    // We need to setup the VAO (Vertex Array object) and the VBO (Vertex Buffer Object)

    // Vertex Array Object (VAO) setup:
    // 
    // - Stores *how* vertex attributes are read
    // - Does NOT store vertex data itself
    
    // Generate a vertex array object
    // Note:
    //   We can think of the VAO as a 'wrapper around' all of the Vertex Buffer Objects, in a sense
    // that it encapsulates all VBO state that we are setting up. 
    //   Thus, it is also important that we glBindVertexArray (i.e. select the VAO to use)
    glGenVertexArrays(1,        // Specifies the number of vertex array object to generate.
                      &_vao);   // OpenGL use an integer that's sort of a handler of the object
    //                 ^~~~ 
    // OpenGL maps _vao → internal VAO object

    // Selects the vao we just create
    glBindVertexArray( _vao );
    
    // Note: 
    //   OpenGL is a C Specification, this means that OpenGL objects are not C++ objects.
    // They are driver-managed resources referenced by integer handles (GLuint) such as 
    // file descriptors in sockets or files. In this case, '_vao' is the handle of the VAO.
    //
    // void glGenVertexArrays(	GLsizei n, GLuint* arrays);
    //                           
    //      n       -  Number of VAO IDs (handles) to generate
    //      arrays  -  Pointer to memory where the IDs will be written



    // Vertex Buffer Object (VBO) creation:
    // 
    // - Stores actual vertex data in GPU memory

    switch (layout) {
        case GeometryLayout::SingleVBO:
        {
             _setup_single_vbo(vertices);
            break;
        }   
        case GeometryLayout::InterleavedVBO:
        {
             _setup_interleaved_vbo(vertices_n_colors);
            break;
        }   
        case GeometryLayout::MultipleVBOs:
        {
            _setup_multiple_vbos(vertices, colors);
            break;
        }   
    }

    // IMPORTANT:
    // - Attribute enable state is stored in the VAO
    // - Do NOT disable it here
    // Unbind our currently bound VAO
    glBindVertexArray(0);

    // Note: default object ID 0
    //   In OpenGL, object name 0 has a special meaning: Binding object 0 means “unbind the currently bound object and 
    // bind the default object”. In other words, "stop using any VAO. No VAO is currently bound.”
    //
    // Why do people unbind the VAO after setup?
    //   This is a defensive state-management habit. During setup:
    // 
    //          glBindVertexArray(_vao);
    //          glEnableVertexAttribArray(0);
    //      glVertexAttribPointer(...);
    // 
    //   At this point, the VAO:
    // 
    //      - Remembers which attributes are enabled
    //      - Remembers how attribute 0 reads from the VBO
    //      - Remembers which VBO was bound to GL_ARRAY_BUFFER
    // 
    //  Then: glBindVertexArray(0); You’re saying:
    // 
    //   “VAO setup is finished. I don’t want accidental state changes to modify it.”
    //   This prevents bugs later when:
    // 
    //      Another VAO is created
    //      Another buffer is bound
    //      Another attribute pointer is configured
    // 
    // So unbinding is good practice, especially for learning.

    // Disable any attributes we opened in our Vertex Attribute Array
    // as we do not want to leave them opened
    // glDisableVertexAttribArray(0);   // Im not sure about this line
}



void Renderer::_setup_single_vbo(const std::vector<GLfloat>& vertices)
{
    // Creates a new vertext buffer object (VBO) in the GPU
    // Note:
    //   We will see this pattern of code often in OpenGL of creating and binding to a buffer
    glGenBuffers(1, 
                 &_vbo );
    
    // Bind is equivalent to 'selecting the actuve buffer object' that we want to work with in OpenGL
    glBindBuffer( GL_ARRAY_BUFFER,  // GLenum target,  // Defines the information the buffer will store
    //            ^~~~~~~~~~~~~~~
    //      To access Vertex attributes
                  _vbo);            // VBO id 


    // Upload data to GPU:
    //    Now, in our currently binded buffer, we populate the data from our 'vertices' (which is on the CPU)
    // onto a buffer that will be on the GPU
    
    // Store vertices into a VBO
    glBufferData(GL_ARRAY_BUFFER,                       // GLenum target : kind of buffer
                 vertices.size() * sizeof(GLfloat),     // size: Specifies the size in bytes of the buffer object's new data store
                 vertices.data(),
                 GL_STATIC_DRAW );                      // GLenum usage:  Specifies the expected usage pattern of the data store. 
      //         ^~~~~~~~~~~~~~~                           The symbolic constant must be 
      //      data will not change often             GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, 
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
                          3,             // number of components,  (x, y , z)
                          GL_FLOAT,      // GLenum type
                          GL_FALSE,      // normalized?
                          0,             // stride
                                         // 0 is used when we have only one attribute
                          (void*) 0);    // offset

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


void Renderer::_setup_interleaved_vbo(const std::vector<GLfloat>& vertices_data )
{
    //           VAO (_vao)   
    //          ┌───────────────────────────────────┐  
    //          | ┌──────────────────────────────┐  |            VBO (_vbo)
    //          | | name      | type  | location |  |            [ x,y,z,r,g,b,  x,y,z,r,g,b,  x,y,z,r,g,b, ]
    //          | | position  | vec3  | 0        |--|------┐       ^     ^
    //          | | colors    | vec3  | 1        |--|---┐  └-------┘     |
    //          | └──────────────────────────────┘  |   └----------------┘
    //          └───────────────────────────────────┘

    // Creates a VBO in the GPU
    glGenBuffers( 1, &_vbo );
    glBindBuffer( GL_ARRAY_BUFFER, _vbo);

    // Upload data to GPU
    glBufferData(GL_ARRAY_BUFFER,                       
                 vertices_data.size() * sizeof(GLfloat),
                 vertices_data.data(),
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*) 0 );
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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)( 3 * sizeof(GLfloat) ) );
    //                       ^                                       ^ 
    //                      (r,g,b)                                offset  


}

void Renderer::_setup_multiple_vbos(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& colors)
{
    //           VAO (_vao)   
    //          ┌───────────────────────────────────┐  
    //          | ┌──────────────────────────────┐  |
    //          | | name      | type  | location |  |             VBO (_vbos[0])
    //          | | position  | vec3  | 0        |--|------------>[ x,y,z,  x,y,z,  x,y,z ]
    //          | | colors    | vec3  | 1        |--|---┐         VBO (_vbos[1])
    //          | └──────────────────────────────┘  |   └-------->[ r,g,b,  r,g,b,  r,g,b ]
    //          └───────────────────────────────────┘
    
    _vbos.resize(2);

    glGenBuffers(2, _vbos.data() );

    // Upload data to GPU:
    
    // positions
    glBindBuffer( GL_ARRAY_BUFFER, _vbos[0] ); 
    glBufferData( GL_ARRAY_BUFFER,                       // GLenum target : kind of buffer
                  vertices.size() * sizeof(GLfloat),     // size: Specifies the size in bytes of the buffer object's new data store
                  vertices.data(),
                  GL_STATIC_DRAW );                      // GLenum usage:  Specifies the expected usage pattern of the data store. 
    
    // we need to enable and point the VAO attribute o the current bound buffer
    // Note:
    //   glVertexAttribPointer records a relationship between an attribute index and the buffer currently bound to GL_ARRAY_BUFFER.
    // That's why 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    
    // colors
    glBindBuffer( GL_ARRAY_BUFFER, _vbos[1] ); 
    glBufferData( GL_ARRAY_BUFFER,                       // GLenum target : kind of buffer
                  colors.size() * sizeof(GLfloat),     // size: Specifies the size in bytes of the buffer object's new data store
                  colors.data(),
                  GL_STATIC_DRAW );                  

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}


// Step 2: Shader pipeline creation
// 
// Goal:
// - Compile vertex + fragment shaders
// - Link them into a usable GPU program
// 
// Pipeline stages:
// - Vertex Shader
// - Fragment Shader
void Renderer::create_graphics_pipeline(const std::string& shaders_dir)
{
  _shader_program  = create_shader_program(shaders_dir);
}

// Step 3: Frame preparation
// 
// Goal:
// - Configure GPU state
// - Clear framebuffer
// - Activate shader program
/**
 * Pre-Draw typically we will use this for setting some sort of 'state'
 * Note: some of the calls may take place at different stages (post-processing) of the pipline
 * 
 * @return void
 */
void Renderer::pre_draw(int width, int height) const
{
    //   Depth testing determines which fragment is visible when multiple fragments map to the same pixel.
    //
    //   Each fragment has a depth value (z) so OpenGL compares it against the depth buffer
    // Only the fragment that passes the test is drawn
    //
    //   As we are drawing a single 2D triangle, there is No overlapping geometry so no need for depth testing
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // The viewport maps Normalized Device Coordinates (NDC) to window pixels.
    glViewport(0, 0,  // Bottom-left corner: (0, 0)
               width, 
               height);

    // Defines the color used when clearing the color buffer.
    //           r  , g,   b,   a  
    //           ^~~  ^~~  ^~~  ^~~ 
    glClearColor(1.f, 1.f, 0.f, 1.f); // Yellow background

    // Clears one or more framebuffer attachments.
    //
    //   In this case:
    //      Depth buffer → reset to default depth (1.0)
    //      Color buffer → filled with glClearColor
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Selects the active shader program.
    glUseProgram(_shader_program);    
}

/** Draw: 
 *   The render function gets called once per loop.
 *   Typically this inluces 'glDraw' related calls, and the relevant setup of buffers for those calls.
 * 
 * @return void
 * 
 * Note: 
 *   Step 4: Draw call
 * 
 *   Goal:
 *      - Bind geometry description
 *      - Tell GPU how many vertices to render
 */
void Renderer::draw() const
{
    // Enable our attributes
    glBindVertexArray(_vao);
    // Select the vertex buffer object we want to enable
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Render data
    glDrawArrays(GL_TRIANGLES, 0, 3); 
    //                         ^  ^ end vertex
    //                       start vertex

    // Stop using our current graphics pipeline
    // Note: this is not necessary if we only have one graphics pipline.
    glUseProgram(0);
}


std::string Renderer::read_file(std::string_view path) const
{
    std::ifstream ifs(path.data());
    if(!ifs.good())
    {
        std::cerr << path << " cannot be open\n"; 
        throw std::runtime_error("Shader program cannot be read" );
    
    }
    
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

/** Compile shader will compila any valid vertex, fragment, geometry, tesselation or compute shader
 *
 * @param   type      We use the 'type' field to determine which shader we are going to compile
 * @param   source    The shader source code
 * @return  id of the shader object 
 */
GLuint Renderer::compile_shader(GLenum type, const std::string& source) const
{
    GLuint shared_object;
    if( type == GL_VERTEX_SHADER)
        shared_object = glCreateShader(GL_VERTEX_SHADER);
    else if(type == GL_FRAGMENT_SHADER)
        shared_object = glCreateShader(GL_FRAGMENT_SHADER);
    
    const char* src = source.c_str();
    glShaderSource(shared_object, 1, &src, nullptr);
    glCompileShader(shared_object);

    // Retrieve the compilation status
    int result;
    glGetShaderiv(shared_object, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shared_object, GL_INFO_LOG_LENGTH, &length);

        std::string logmsg(length, '\0');
        glGetShaderInfoLog(shared_object, length, &length, logmsg.data());     
        
        // Delete out broken shader
        glDeleteShader(shared_object);

        throw renderer_error( (type == GL_VERTEX_SHADER? "VERTEX SHADER: ": "FRAGMENT SHADER: ") + logmsg );
    }

    return shared_object;
}

/** Creates a graphics program object (i.e. graphics pipeline) with a Vertex Shader and a Fragment Shader
 * @return id of the program Object.
 * 
 * Note: A shader program defines programmable stages of the graphics pipeline and becomes active when bound using glUseProgram.
 */
GLuint Renderer::create_shader_program(const std::string& shaders_dir) const
{
    // Creates a new program object
    GLuint program = glCreateProgram();

    // Compile our shaders
    GLuint vs = compile_shader( GL_VERTEX_SHADER,
                                read_file(shaders_dir + "/vertex.glsl") );
    GLuint fs = compile_shader( GL_FRAGMENT_SHADER,
                                read_file(shaders_dir + "/fragment.glsl") );

    // Link our two shader programs ogether
    // Consider this the equivalent of taking two .cpp files and linking them into one executable fie
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    // Check link status
    GLint linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE)
    {
        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        std::string logmsg(length, '\0');
        glGetProgramInfoLog(program, length, nullptr, logmsg.data());

        glDeleteProgram(program);
        throw renderer_error("Shader link error: " + logmsg);
    }

    // Validate our program
    glValidateProgram(program);
  
    // Once our final program object has been created, we can detach and then delete our individual shaders
    glDetachShader(program, vs);
    glDetachShader(program, fs);

    // Shaders no longer needed after linking
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


