#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>    

#include "GeometryData.h"
#include "Shader.h"


struct GPUObject
{
  public:
        explicit GPUObject(const GeometryData& cpu_data);
        ~GPUObject();

        void upload_to_gpu();
        // Note: we need to create the vertex and a fragment shaders after the GPU object (VAO+VBO) is store in the CPU
        // since the shaders uses the VAO and VBO
        void create_shader();
        void enable_shader();

        void draw() const;
  
  private:
  
        //
        // ---- CPU-side data ----
        //
        GeometryData _cpu_data;
  
        //
        // ---- GPU-side objects ----
        //
        
        // OpenGL object handles (IDs):
        GLuint _vao{0};
        GLuint _vbo{0};

        // Shader Program : defines vertex + fragment processing
        Shader _shader;
  };