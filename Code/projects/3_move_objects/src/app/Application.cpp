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

void Application::run() 
{
    // 1. Setup the grapichs program
    // Create and SDL window + GL context
    GLWindow window(640, 480);

    mouse_setup(window);

    // Create renderer AFTER GL context exists
    Renderer renderer{};

    // 2. Creates the vertices in the CPU and then transfering 
    // these ti the GPU using GL commands 
    Mesh m1(GeometryData::make_triangle());
    Mesh m2(GeometryData::make_quad());
    
    m1.upload_to_gpu();
    m2.upload_to_gpu();
    
    // 3. Create our graphics pipline
    //    - At a minimumm, this means setting up the vertex and fragment shader
    //   which means laoding the shaders, compile them and linking them together
    auto shader = std::make_shared<Shader>("/tmp/gl/shaders");
    shader->create();
    
    Material material(shader);

    auto r1{ std::make_shared<Renderable>(&m1, &material) };
    auto r2{ std::make_shared<Renderable>(&m2, &material) };
    r1->transform.position.x = 1;
    r2->transform.position.x = -1;

    std::vector< std::shared_ptr<Renderable> > renderables{ r1,  r2};

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
    // Camera     → produces view/projection matrix and we upload as uniforms to be used in shaders
    //
    // NOTE: in a real game, we might have multiple cameras (Strategy desing pattern) where you can change the view
    Camera camera{window.width(), window.height()};
    
    // 4. Main loop
    while (!_quit)
    {
        // Always rotate r2
        r2->transform.rotation.y += 0.1f;
 
        // input
        read_input(r1->transform, camera);

        // Setup anything (i.e. OpenGL state) that needs to take place before draw calls
        // Usually, setup the background and uploads uniforms used for all the renderables
        renderer.pre_draw(material, camera);
        // Draw calls in OpenGL
        renderer.draw(renderables);

        // Update screen of our specified windows
        window.render();
    }
}


void Application::read_input(Transform& transform, Camera& camera)
{   
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if ( e.type == SDL_QUIT )
        {
            std::cout << "Goodbye\n";
            _quit = true;
        }
        if(e.type == SDL_MOUSEMOTION)
        {
            camera.mouse_look( e.motion.xrel, e.motion.yrel );
        }
    }

    // Retrive keyboard state
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if( state[SDL_SCANCODE_ESCAPE])
    {
        std::cout << "Goodbye\n";
        _quit = true;
    }
    
    // Camera
    if( state[SDL_SCANCODE_UP])    camera.move_forward(0.01f);
    if( state[SDL_SCANCODE_DOWN])  camera.move_backward(0.01f);
    if( state[SDL_SCANCODE_LEFT])  camera.move_left(0.01f);
    if( state[SDL_SCANCODE_RIGHT]) camera.move_right(0.01f);

    /*   
    // Camera perspective: zoom in/out
    if( state[SDL_SCANCODE_UP])
        transform.position.z += 0.01f;
        //                 ^~
        //   TODO: Fix me, Im moving the object, not the camera
    if( state[SDL_SCANCODE_DOWN])
        transform.position.z -= 0.01f;
        //                 ^~
        //   TODO: Fix me, Im moving the object, not the camera
   */ 
    // Transformations:
    // Movement
    if( state[SDL_SCANCODE_W]) transform.position.y += 0.01f;
    if( state[SDL_SCANCODE_S]) transform.position.y -= 0.01f;
    if( state[SDL_SCANCODE_D]) transform.position.x += 0.01f;
    if( state[SDL_SCANCODE_A]) transform.position.x -= 0.01f;
    if( state[SDL_SCANCODE_1]) transform.position.z += 0.01f;
    if( state[SDL_SCANCODE_2]) transform.position.z -= 0.01f;
    // Rotation
    if( state[SDL_SCANCODE_Q]) transform.rotation.y -= 1.0f;
    if( state[SDL_SCANCODE_E]) transform.rotation.y += 1.0f;
    if( state[SDL_SCANCODE_3]) transform.rotation.x -= 1.0f;
    if( state[SDL_SCANCODE_4]) transform.rotation.x += 1.0f;
    if( state[SDL_SCANCODE_5]) transform.rotation.z -= 1.0f;
    if( state[SDL_SCANCODE_6]) transform.rotation.z += 1.0f;
    // Scale
    if( state[SDL_SCANCODE_RIGHTBRACKET]) transform.scale += 0.01f;
    if( state[SDL_SCANCODE_SLASH])        transform.scale -= 0.01f;

    if( state[SDL_SCANCODE_R]) transform.reset();

}