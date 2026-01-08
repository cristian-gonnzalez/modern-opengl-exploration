#pragma once


#include <vector>
#include <string>
#include <string_view>
#include <iostream>

#include <glad/glad.h> 


// IMPORTANT:
//   Only one shader object can be active at the time in OpenGL. This means that I could have one
// shader program for multiple GPU objects. Or multiple shaders for multiple GPU objects but I have
// to make sure to call glUseProgram before updating uniform varibales or drawing.
class Shader
{
    public:
        Shader(const std::string& shaders_dir);
        ~Shader();

        // Copy semantics
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        // Move semantics
        Shader(Shader&& other) noexcept
        : _shader_program(other._shader_program),
          _shaders_dir(std::move(other._shaders_dir))
        {
            other._shader_program = 0;
        }

        Shader& operator=(Shader&& other) noexcept
        {
            if (this != &other) 
            {
                // Moves a resoruce in OpenGL is move the handle id, not copying GPU data
                _shader_program = other._shader_program;

                // Leave the other object in valid state
                other._shader_program = 0;
            }
            return *this;
        }

        // Copy semantics

        void create();
        void enable();
        void update_uvar(const std::string u_var_name, float value)
        {
            // glUniform* ALWAYS update the program that is active.
            enable();

            // Returns the location of a uniform variable
            GLint location = glGetUniformLocation( _shader_program,
                                                   u_var_name.c_str());
            if( location < 0)
            {
                std::cerr << "location " << u_var_name << " not found\n";
                return;
            }
            
            glUniform1f(location, value);  
        }

    private:        
        // Stores the unique id for the grapichs pipeline program object that will be used for our OpenGL draw calls.
        // NOTE:
        //    This is a handle ID that manages a GPU resourse, so we need to define Copy/Move semantics to habndle this 
        GLuint            _shader_program{0};
        const std::string _shaders_dir;

        // TODO: We could have a list of uniform variables shared with the shaders
        // std::vector< const std::string > _uniform_variables{}; 
        
        // ---- Shader helpers ----
        std::string read_file( std::string_view path ) const;
        GLuint      compile_shader( GLenum type, const std::string& source ) const;
        GLuint      create_shader_program( const std::string& shaders_dir ) const;     
        
        GLint get_uniform_location( std::string u_var_name )
        {
            // Returns the location of a uniform variable
            GLint location = glGetUniformLocation( _shader_program,
                                                   u_var_name.c_str());
            if( location < 0)
                std::cerr << "location " << u_var_name << ": " << location << std::endl;
            
            return location;
        }

};
