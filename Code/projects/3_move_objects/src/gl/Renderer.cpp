#include "Renderer.h"

#include <iostream>
#include <stdexcept>

#include "Mesh.h"
#include "Shader.h"

 
class renderer_error : public std::runtime_error
{
    public:
        explicit renderer_error(const std::string& msg)
        : std::runtime_error(msg) 
        {}
};




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
void Renderer::pre_draw(const std::vector< std::shared_ptr<Renderable> >& objects, const Camera& camera, int width, int height)
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
    Shader* current = nullptr;
    for (const auto& r : objects) 
    {
        if( &r->material->shader() != current) 
        {
            current = &r->material->shader();
            current->use();
        }

#ifdef UV
        r->material->bind( r->transform.position.y );
#else
        r->material->set_transform( r->transform.get_model_matrix() );
#endif
        r->material->set_projection( camera.get_projection_matrix() ); 
    }
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
void Renderer::draw(const std::vector< std::shared_ptr<Renderable> >& objects) 
{    
    Shader* current = nullptr;
    for (const auto& r : objects) 
    {
        if( &r->material->shader() != current) 
        {
            current = &r->material->shader();
            current->use();
        }
        r->mesh->draw();
    }

    glUseProgram(0);
}