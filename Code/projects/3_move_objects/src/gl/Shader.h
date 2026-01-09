#pragma once


#include <vector>
#include <string>
#include <string_view>
#include <iostream>

#include <glad/glad.h> 
#include <glm/ext/matrix_transform.hpp>

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
                // remove the old shader program if we had one
                if (_shader_program != 0)
                    glDeleteProgram(_shader_program);

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
        void set_model_matrix( float y_offset )
        {
            auto [success, location] = _get_uv_location("u_model_matrix");
            if( success )
            {
                                     //      unit matrix   
                                     //       ^~~~~~~~~~~~~~   
                glm::mat4 model = glm::translate( glm::mat4(1.0f), 
                                                glm::vec3( 0.0f, y_offset, 0.0f) );             
                glUniformMatrix4fv( location, 
                                    1,
                                    GL_FALSE,
                                    &model[0][0]);
            }     
        }

        void update_uv(const std::string uv_name, float value)
        {
            auto [success, location] = _get_uv_location(uv_name);
            if( success )
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


        std::pair<bool, GLint> _get_uv_location(const std::string uv_name)
        {
            // glUniform* ALWAYS update the program that is active.
            enable();

            // Returns the location of a uniform variable
            GLint location = glGetUniformLocation( _shader_program,
                                                   uv_name.c_str());
            bool success = ( location >= 0);
            if(!success)
                std::cerr << "location " << uv_name << " not found\n";
            
            return {success, location};  
        }
};
