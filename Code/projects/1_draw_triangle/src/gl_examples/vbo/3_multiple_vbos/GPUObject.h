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
        // Shaders define how vertex attributes are interpreted during rendering. They must match the VAO attribute layout.
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
        
        // Verter Array Object (VAO):
        //   It contains only attributes desctiptions that describes how vertex data is interpreted.
        GLuint _vao{0};
        
        // Vertex Buffer Object (VBO)
        //   Vertex Buffer Objects store information relating to vertices (e.g. position, normals, textures) on the GPU.
        std::vector<GLuint> _vbos;  // Use in multiple VBO example

        // Shader Program : defines vertex + fragment processing
        Shader _shader;
  };