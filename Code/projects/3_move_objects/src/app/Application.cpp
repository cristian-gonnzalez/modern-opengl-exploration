#include "Application.h"
#include "GLWindow.h"
#include "Renderer.h"
#include "Material.h"
#include "GeometryData.h"
#include "Mesh.h"
#include "Camera.h"
#include "Renderable.h"

#include <SDL2/SDL.h>         // SDL_init 

#include <iostream>
#include <stdexcept>
#include <utility>
#include <memory>

// Using a static helper function in a .cpp file provides internal linkage and avoids polluting the global namespace 
// while enabling concise, informative error reporting.
static std::runtime_error sdl_error(const char* msg)
{
    return std::runtime_error( std::string("[SDL] ") + msg + ": " + SDL_GetError() );
}

Application::Application()
{
    // RAII
    if( SDL_Init(SDL_INIT_VIDEO) < 0)
        throw sdl_error("Could not initialize video subsystem");
}
Application::~Application()
{
    // RAII
    SDL_Quit();
}

void Application::run( const GeometryData& geo_data ) 
{
    // 1. Setup the grapichs program
    // Create and SDL window + GL context
    GLWindow window(640, 480);

    // Create renderer AFTER GL context exists
    Renderer renderer{};

    // 2. Creates the vertices in the CPU and then transfering 
    // these ti the GPU using GL commands 
    Mesh shape(geo_data);
    shape.upload_to_gpu();
    
    // 3. Create our graphics pipline
    //    - At a minimumm, this means setting up the vertex and fragment shader
    //   which means laoding the shaders, compile them and linking them together
    auto shader = std::make_shared<Shader>("/tmp/gl/shaders");
    shader->create();
    
    Material material(shader);

    auto rend_obj{ std::make_shared<Renderable>(&shape, &material) };

    std::vector< std::shared_ptr<Renderable> > renderables{ rend_obj };

    // In OpenGL itself: there is no camera.
    // OpenGL only knows about:
    // 
    // - Buffers
    // - Vertex arrays
    // - Shaders
    // - Uniforms
    // - Draw calls
    // 
    // A “camera” is just a set of uniform values
    // Camera     → produces view/projection data
    Camera camera{window.width(), window.height()};
    
    // 4. Main loop
    while (!_quit)
    {
        // input
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                std::cout << "Goodbye\n";
                _quit = true;
            }
        }

        // Retrive keyboard state
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // Camera perspective: zoom in/out
        if( state[SDL_SCANCODE_UP])
            rend_obj->transform.position.z += 0.01f;
        if( state[SDL_SCANCODE_DOWN])
            rend_obj->transform.position.z -= 0.01f;
        
        // Transformations:
        // Movement
        if( state[SDL_SCANCODE_W])
            rend_obj->transform.position.y += 0.01f;
        if( state[SDL_SCANCODE_S])
            rend_obj->transform.position.y -= 0.01f;
        if( state[SDL_SCANCODE_D])
            rend_obj->transform.position.x += 0.01f;
        if( state[SDL_SCANCODE_A])
            rend_obj->transform.position.x -= 0.01f;
        // Rotation
        if( state[SDL_SCANCODE_LEFT])
            rend_obj->transform.rotation.y -= 1.0f;
        if( state[SDL_SCANCODE_RIGHT])
            rend_obj->transform.rotation.y += 1.0f;
        // Scale
        if( state[SDL_SCANCODE_Q])
            rend_obj->transform.scale += 0.01f;
        if( state[SDL_SCANCODE_E])
            rend_obj->transform.scale -= 0.01f;
  
        // Setup anything (i.e. OpenGL state) that needs to take place before draw calls
        renderer.pre_draw(window.width(), window.height());
        // Draw calls in OpenGL
        renderer.draw(renderables, camera);

        // Update screen of our specified windows
        window.render();
    }
}

