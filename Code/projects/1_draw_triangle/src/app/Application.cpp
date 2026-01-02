#include "Application.h"
#include "GLWindow.h"
#include "Renderer.h"

#include <SDL2/SDL.h>         // SDL_init 

#include <iostream>
#include <stdexcept>
#include <utility>

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

void Application::run() 
{
    // 1. Setup the grapichs program
    // Create and SDL window + GL context
    GLWindow window(640, 480);

    // 2. Create renderer AFTER GL context exists
    Renderer renderer;
    // Creates the vertices in the CPU and then transfering 
    // thise ti the GPU using GL commands 
    renderer.setup_geometry();

    // 3. Create our graphics pipline
    //    - At a minimumm, this means setting up the vertex and fragment shader
    //   which means laoding the shaders, compile them and linking them together
    renderer.create_graphics_pipeline();

    // 3. Main loop
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

        // Setup anything (i.e. OpenGL state) that needs to take place before draw calls
        renderer.pre_draw(window.width(), window.height());
        // Draw calls in OpenGL
        renderer.draw();

        // Update screen of our specified windows
        window.render();
    }
}



