#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

class shader_error : public std::runtime_error
{
    public:
        explicit shader_error(const std::string& msg)
        : std::runtime_error(msg) 
        {}
};

Shader::Shader(const std::string& shaders_dir)
:_shaders_dir{shaders_dir}
{
}

Shader::~Shader()
{        
    if (_shader_program)
        glDeleteProgram(_shader_program);
}

void Shader::create()
{
    _shader_program = create_shader_program(_shaders_dir);
}

void Shader::enable()
{       
    // Selects the active shader program.
    glUseProgram(_shader_program);      
}

std::string Shader::read_file(std::string_view path) const
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
GLuint Shader::compile_shader(GLenum type, const std::string& source) const
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

        throw shader_error( (type == GL_VERTEX_SHADER? "VERTEX SHADER: ": "FRAGMENT SHADER: ") + logmsg );
    }

    return shared_object;
}


/** Creates a graphics program object (i.e. graphics pipeline) with a Vertex Shader and a Fragment Shader
 * @return id of the program Object.
 * 
 * Note: A shader program defines programmable stages of the graphics pipeline and becomes active when bound using glUseProgram.
 */
GLuint Shader::create_shader_program(const std::string& shaders_dir) const
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
        throw shader_error("Shader link error: " + logmsg);
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
