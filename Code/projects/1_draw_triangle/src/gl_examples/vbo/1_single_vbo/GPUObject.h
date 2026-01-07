#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>    

#include "GeometryData.h"
#include "Shader.h"

/** GPUObject encapsulates VAO + VBO + Shader
 * 
 *     VAO + VBO belong together
 *     Shader belongs with the geometry it draws (for now)
 */
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
        
        // OpenGL object handles (IDs):
        //
        // IMPORTANT: 
        //   OpenGL is a C-Specification, this means that OpenGL objects are not C++ objects.
        // They are driver-managed resources referenced by integer handles (GLuint) such as 
        // file descriptors in sockets or files. In this case, '_vao' is the handle of the VAO.
        //
        // void glGenVertexArrays(	GLsizei n, GLuint* arrays);
        //                           
        //      n       -  Number of VAO IDs (handles) to generate
        //      arrays  -  Pointer to memory where the IDs will be written
        //
 
        // Verter Array Object (VAO):
        //   It contains only attributes desctiptions that describes how vertex data is interpreted.
        //
        //   Verter array objects encapsulate all of the items needed to render an object.
        // For example, we may have multiple vertex buffer objects (VBO) related to rendering
        // one object. The VAO allows us to setup the OpenGL state to render that using the 
        // correct layout and the correct bufers with one call after being setup.
        GLuint _vao{0};
    //  ^~~~~~ ^~~~ 
    //    |    '_vao' is a handle (descriptor or ID), the actual VAO lives inside the OpenGL driver
    //    |
    // GLuint is an OpenGL-defined unsigned integer type used to represent object handles (IDs).
        
        // Vertex Buffer Object (VBO)
        //   Vertex Buffer Objects store information relating to vertices (e.g. position, normals, textures) on the GPU.
        // VBOs are our mechanism for arranging geometry on the GPU
        GLuint _vbo{0};

        // Shader Program : defines vertex + fragment processing
        Shader _shader;
  };