#include "Renderer.h"

#include <iostream>
#include <stdexcept>
 
class renderer_error : public std::runtime_error
{
    public:
        explicit renderer_error(const std::string& msg)
        : std::runtime_error(msg) 
        {}
};

void Renderer::add( const GeometryData& data )
{
    _gpu_objs.emplace_back(data);
}


// Step 1: Geometry specification (CPU → GPU)
// 
// Goal:
// - Upload vertex data to GPU memory
// - Describe how that data should be interpreted
// 
// Pipeline stage:
// - Vertex Specification (before vertex shader)
void Renderer::setup_geometry()
{
    for(auto& e: _gpu_objs)
        e.upload_to_gpu();

    // IMPORTANT:
    // - Attribute enable state is stored in the VAO
    // - Do NOT disable it here
    // Unbind our currently bound VAO
    glBindVertexArray(0);

    // Note: default object ID 0
    //   In OpenGL, object name 0 has a special meaning: Binding object 0 means “unbind the currently bound object and 
    // bind the default object”. In other words, "stop using any VAO. No VAO is currently bound.”
    //
    // Why do people unbind the VAO after setup?
    //   This is a defensive state-management habit. During setup:
    // 
    //          glBindVertexArray(_vao);
    //          glEnableVertexAttribArray(0);
    //      glVertexAttribPointer(...);
    // 
    //   At this point, the VAO:
    // 
    //      - Remembers which attributes are enabled
    //      - Remembers how attribute 0 reads from the VBO
    //      - Remembers which VBO was bound to GL_ARRAY_BUFFER
    // 
    //  Then: glBindVertexArray(0); You’re saying:
    // 
    //   “VAO setup is finished. I don’t want accidental state changes to modify it.”
    //   This prevents bugs later when:
    // 
    //      Another VAO is created
    //      Another buffer is bound
    //      Another attribute pointer is configured
    // 
    // So unbinding is good practice, especially for learning.

    // Disable any attributes we opened in our Vertex Attribute Array
    // as we do not want to leave them opened
    // glDisableVertexAttribArray(0);   // Im not sure about this line
}



// Step 2: Shader pipeline creation
// 
// Goal:
// - Compile vertex + fragment shaders
// - Link them into a usable GPU program
// 
// Pipeline stages:
// - Vertex Shader
// - Fragment Shader
void Renderer::create_graphics_pipeline()
{
    for(auto& e: _gpu_objs)
        e.create_shader();
}

// Step 3: Frame preparation
// 
// Goal:
// - Configure GPU state
// - Clear framebuffer
// - Activate shader program
/**
 * Pre-Draw typically we will use this for setting some sort of 'state'
 * Note: some of the calls may take place at different stages (post-processing) of the pipline
 * 
 * @return void
 */
void Renderer::pre_draw(int width, int height)
{
    //   Depth testing determines which fragment is visible when multiple fragments map to the same pixel.
    //
    //   Each fragment has a depth value (z) so OpenGL compares it against the depth buffer
    // Only the fragment that passes the test is drawn
    //
    //   As we are drawing a single 2D triangle, there is No overlapping geometry so no need for depth testing
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // The viewport maps Normalized Device Coordinates (NDC) to window pixels.
    glViewport(0, 0,  // Bottom-left corner: (0, 0)
               width, 
               height);

    // Defines the color used when clearing the color buffer.
    //           r  , g,   b,   a  
    //           ^~~  ^~~  ^~~  ^~~ 
    glClearColor(1.f, 1.f, 0.f, 1.f); // Yellow background

    // Clears one or more framebuffer attachments.
    //
    //   In this case:
    //      Depth buffer → reset to default depth (1.0)
    //      Color buffer → filled with glClearColor
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Selects the active shader program.
//    glUseProgram(_shader_program);    
}

/** Draw: 
 *   The render function gets called once per loop.
 *   Typically this inluces 'glDraw' related calls, and the relevant setup of buffers for those calls.
 * 
 * @return void
 * 
 * Note: 
 *   Step 4: Draw call
 * 
 *   Goal:
 *      - Bind geometry description
 *      - Tell GPU how many vertices to render
 */
void Renderer::draw()
{
    for (auto& obj : _gpu_objs)
    {
        obj.enable_shader();
        obj.draw();
    }
    
    // Stop using our current graphics pipeline
    // Note: this is not necessary if we only have one graphics pipline.
    glUseProgram(0);
}


