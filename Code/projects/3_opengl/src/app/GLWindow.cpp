#include "GLWindow.h"


// Using a static helper function in a .cpp file provides internal linkage and avoids polluting the global namespace 
// while enabling concise, informative error reporting.
static std::runtime_error gl_error(const char* msg)
{
    return std::runtime_error( std::string("[GLWindow] ") + msg + ": " + SDL_GetError() );
}

GLWindow::GLWindow(int width, int height)
: _width{width}, _height{height}
{
    // RAII
    // Creates an application window using OpenGL that supports SDL
    _window = SDL_CreateWindow( "OpenGL Window",       // title
                                0, 0,                  // x, y, 
                                width, height,              
                                SDL_WINDOW_OPENGL );   // flags 
    if( _window == nullptr )
        throw gl_error("SDL window could not be created");
    
    _create_gl_contex();
}

GLWindow::~GLWindow()
{
    // RAII
    if (_gl_ctx)
        SDL_GL_DeleteContext(_gl_ctx);

    if (_window)
        SDL_DestroyWindow(_window);
}



void GLWindow::render()
{
    // Swap buffers: 
    //   SDL2 has doulble-buffer strategy. This means that we have been drawing in our scene (some back buffer)
    // and we need this to present to the actual screen
    SDL_GL_SwapWindow( _window );
}


void GLWindow::_create_gl_contex()
{   
    if( _window == nullptr)
        throw std::runtime_error("OpenGL Window should have been created");
            
    // Set OpenGL 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    // We want to enforce use modern OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // We want to request a double buffer for smooth updating
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // We need to still to setup our OpenGL Graphics context
    _gl_ctx = SDL_GL_CreateContext( _window ); // Create an OpenGL context for an OpenGL window, and make it current.
    if( _gl_ctx == nullptr)
        throw gl_error("OpenGL context could not be created");
    
    // Enable VSync
    SDL_GL_SetSwapInterval(1);

    // Initializes the Glad library
    // This library brings all the OpenGL functions 
    if( !gladLoadGLLoader(SDL_GL_GetProcAddress) )
        throw std::runtime_error("Failed to initialize GLAD");

    _print_gl_info();
}

void GLWindow::_print_gl_info() const
{
    std::cout << "Vendor          : " << glGetString( GL_VENDOR ) << std::endl
                << "Renderer        : " << glGetString( GL_RENDERER ) << std::endl
                << "Version         : " << glGetString( GL_VERSION ) << std::endl
                << "Shading language: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
}
