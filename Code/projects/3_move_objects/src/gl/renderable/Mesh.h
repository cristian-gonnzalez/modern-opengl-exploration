#pragma once

#include <vector>
#include <memory>
#include <string>

// Third party libraries
#include <glad/glad.h>    
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

// Applications
#include "GeometryData.h"


/** Mesh: 
 *    Owns GPU geometry resources (VAO, VBO, EBO).
 *    Uploads vertex/index data to the GPU.
 *    Issues draw calls (glDrawElements).
 *
 *    Does NOT know about shaders, materials, or transforms.
 */
struct Mesh
{
  public:
        explicit Mesh(const GeometryData& cpu_data);
        ~Mesh();
        
        // Copy semantics
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        // Move semantics
        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;

        void upload_to_gpu();
        void draw() const;

  private:
  
        //
        // ---- CPU-side data ----
        //
        GeometryData _cpu_data;
  
        //
        // ---- GPU-side objects ----
        //
        // IMPORTANT: This class handles GPU resources (open/close functions) (with RAII -- we adquire in the constructor and then releases in the
        // destructor). This means that the class should define copy and move semantics.

        // OpenGL object handles (IDs):
        GLuint _vao{0};
        GLuint _vbo{0};
        
        // This is used to store the array of indices that we want to draw from, when we do inexed drawing.
        GLuint _ibo{0};
        
        void reset_gpu_handles();
  };