#pragma once


#include <vector>
#include <string>
#include <string_view>
#include <iostream>

#include <glad/glad.h> 

/** Shader
 *
 * Wraps an OpenGL shader program.
 * Compiles, links, and manages program lifetime.
 * Can be bound for rendering via glUseProgram.
 *
 * Represents a GPU pipeline configuration.
 *
 * IMPORTANT:
 *   Only one shader object can be active at the time in OpenGL. This means that I could have one
 * shader program for multiple Renderables objects. Or multiple shaders for multiple Renderables objects 
 * but I have to make sure to call glUseProgram before updating uniform varibales or drawing.
 */
class Shader
{
    public:
        Shader(const std::string& shaders_dir);
        ~Shader();

        // Copy semantics
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        // Move semantics
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        void create();
        void use();

        std::pair<bool, GLint> get_uv_location(const std::string name);

    private:        
        // Stores the unique id for the grapichs pipeline program object that will be used for our OpenGL draw calls.
        // NOTE:
        //    This is a handle ID that manages a GPU resourse, so we need to define Copy/Move semantics to habndle this 
        GLuint            _shader_program{0};
        const std::string _shaders_dir;
        
        // ---- Shader helpers ----
        std::string read_file( std::string_view path ) const;
        GLuint      compile_shader( GLenum type, const std::string& source ) const;
        GLuint      create_shader_program( const std::string& shaders_dir ) const;             
};



