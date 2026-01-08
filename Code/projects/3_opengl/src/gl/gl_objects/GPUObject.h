#pragma once

#include <vector>
#include <string>

// Third party libraries
#include <glad/glad.h>    
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

// Applications
#include "GeometryData.h"
#include "Shader.h"



struct GPUObject
{
  public:
        explicit GPUObject(const GeometryData& cpu_data);
        ~GPUObject();
        
        // Copy semantics
        GPUObject(const GPUObject&) = delete;
        GPUObject& operator=(const GPUObject&) = delete;

        // Move semantics
        GPUObject(GPUObject&& other) noexcept
        : _cpu_data(std::move(other._cpu_data)),
          _vao(other._vao),
          _vbo(other._vbo),
          _ibo(other._ibo),
          _shader(std::move(other._shader))
        {
            other._vao = other._vbo = other._ibo = 0;
        }

        GPUObject& operator=(GPUObject&& other) noexcept
        {
            if (this != &other) 
            {
                  // Moves a resoruce in OpenGL is move the handle id, not copying GPU data
                  _cpu_data = std::move(other._cpu_data);
                  _vao = other._vao;
                  _vbo = other._vbo;
                  _ibo = other._ibo;
                  _shader = std::move(other._shader);

                  // Leaves the other object in valid state
                  other._vao = other._vbo = other._ibo = 0;
            }
            return *this;
        }


        void upload_to_gpu();

        // Note: we need to create the vertex and a fragment shaders after the GPU object (VAO+VBO) is store in the CPU
        // Shaders define how vertex attributes are interpreted during rendering. They must match the VAO attribute layout.
        void create_shader();
        void enable_shader();

        void draw() const;

        void move_up( float offset )
        {
            _y += offset;
            _shader.update_uvar("u_offset", _y);
            
            //std::cout << "_y: " << _y << std::endl;
        }
  
        
        void move_down( float offset )
        {
            _y -= offset;
            _shader.update_uvar("u_offset", _y);
            
            //std::cout << "_y: " << _y << std::endl;
        }
  private:
  
        //
        // ---- CPU-side data ----
        //
        GeometryData _cpu_data;

        float _y{0};
  
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

        // Shader Program : defines vertex + fragment processing
        // IMPORTANTE: 
        //   Only one shader object can be active at the time in OpenGL. This means that I could have one
        // shader program for multiple GPU objects. Or multiple shaders for multiple GPU objects but I have
        // to make sure to call glUseProgram before updating uniform varibales or drawing.
        // 
        //   This made the '_shader' variable defined here as part of one GPU object, a design decision and not 
        // a RULE of OpenGL.
        Shader _shader;
  };