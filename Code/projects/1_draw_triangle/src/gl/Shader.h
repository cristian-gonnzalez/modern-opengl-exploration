#pragma once


#include <vector>
#include <string>
#include <string_view>

#include <glad/glad.h>        // glGetString


class Shader
{
    public:
        Shader(const std::string& shaders_dir);
        ~Shader();

        void create();
        void enable();

    private:        
        // Stores the unique id for the grapichs pipeline program object that will be used for our OpenGL draw calls.
        GLuint _shader_program{0};
        const std::string _shaders_dir;
        
        // ---- Shader helpers ----
        std::string read_file(std::string_view path) const;
        GLuint compile_shader(GLenum type, const std::string& source) const;
        GLuint create_shader_program(const std::string& shaders_dir) const;     
};
