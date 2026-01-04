#pragma once


#include <vector>
#include <string>
#include <string_view>

#include <glad/glad.h>        // glGetString


enum class GeometryLayout {
    SingleVBO,
    InterleavedVBO,
    MultipleVBOs
};

// Owns all OpenGL rendering resources:
// 
// - VAO  : describes how vertex data is interpreted
// - VBO  : stores vertex data on the GPU
// - Shader Program : defines vertex + fragment processing
// 
// This class contains *only OpenGL logic*.
// No SDL, no windowing, no event handling.
class Renderer
{
    public:
        Renderer() = default;
        ~Renderer();

        // Step 1: Upload geometry data (CPU → GPU)
        // Responsible for getting vertex data on the GPU
        void setup_geometry(GeometryLayout layout = GeometryLayout::SingleVBO);

        // Step 2: Create and link the shader pipeline
        // Reponsible for once we have our actual geomerty creating a pipline with a vertex and a fragment
        // shaders
        void create_graphics_pipeline(const std::string& shaders_dir);

        // Step 3: Prepare frame (state + clearing)
        void pre_draw(int width, int height) const;
        // Step 4: Issue draw call
        void draw() const;

    private:        
        // ---- GPU objects ----
        // OpenGL object handles (IDs)
        
        // Verter Array Object (VAO)
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
        //   Vertex Buffer Objects store information relating to verices (e.g. position, normals, textures)
        // VBOs are our mechanism for arranging geometry on the GPU
        GLuint _vbo{0};
        std::vector<GLuint> _vbos;  // Use in multiple VBO example

        // Stores the unique id for the grapichs pipeline program object that will be used for our OpenGL draw calls.
        GLuint _shader_program{0};
        
        // ---- Shader helpers ----
        std::string read_file(std::string_view path) const;
        GLuint compile_shader(GLenum type, const std::string& source) const;
        GLuint create_shader_program(const std::string& shaders_dir) const;     
        
        void _setup_single_vbo(const std::vector<GLfloat>& vertices);
        void _setup_interleaved_vbo(const std::vector<GLfloat>& vertices );
        void _setup_multiple_vbos(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& colors);
};
