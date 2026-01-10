#include "Application.h"
#include "GLWindow.h"
#include "Renderer.h"
#include "Material.h"
#include "GeometryData.h"
#include "Mesh.h"
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

    std::shared_ptr<Renderable> rend_object{std::make_shared<Renderable>()};

    rend_object->material = &material;
    rend_object->mesh = &shape;

    std::vector< std::shared_ptr<Renderable> > _renderables { rend_object };
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
        if( state[SDL_SCANCODE_UP])
        {    
            rend_object->transform.position.y += 0.01f;
        }
        if( state[SDL_SCANCODE_DOWN])
        {   
            rend_object->transform.position.y -= 0.01f;
        }
        

        // Setup anything (i.e. OpenGL state) that needs to take place before draw calls
        renderer.pre_draw(window.width(), window.height());
        // Draw calls in OpenGL
        renderer.draw(_renderables);

        // Update screen of our specified windows
        window.render();
    }
}

