/**  Modern OpenGL
 */
// g++ -std=c++17 main.cpp ./glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
#include <SDL2/SDL.h>         // SDL_init 
#include <SDL2/SDL_video.h>   // SDL_CreateWindow / SDL_GL_SetAttribute / SDL_GL_CreateContext
#include <glad/glad.h>        // glGetString

#include <iostream>
#include <stdexcept>
#include <utility>

// GW Windows manage the Window + GL context
class GLWindow
{
    public:
        GLWindow(int width, int height)
        {
            // RAII
            _window = SDL_CreateWindow( "OpenGL Window",                // title
                                            0, 0,                       // x, y, 
                                            width, height,              
                                            SDL_WINDOW_OPENGL );        // flags 
            if( _window == nullptr )
                throw std::runtime_error("SDL window could not be created");
            
            _create_gl_contex();
        }
        ~GLWindow()
        {
            // RAII
            if (_gl_ctx)
                SDL_GL_DeleteContext(_gl_ctx);

            if (_window)
                SDL_DestroyWindow(_window);
        }

        void render()
        {
            SDL_GL_SwapWindow( _window );
        }

    private:
        SDL_Window*   _window{nullptr};
        SDL_GLContext _gl_ctx{nullptr};

        void _create_gl_contex()
        {   
            if( _window == nullptr)
                throw std::runtime_error("OpenGL Window should have been created");
                 
            // Set OpenGL 4.1
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            
            // We want to enforce use modern OpenGL
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

            // We need to still to setup our OpenGL Graphics context
            _gl_ctx = SDL_GL_CreateContext( _window ); // Create an OpenGL context for an OpenGL window, and make it current.
            if( _gl_ctx == nullptr)
                throw std::runtime_error("OpenGL context could not be created");
            
            // Enable VSync
            SDL_GL_SetSwapInterval(1);

            // Initializes the Glad library
            if( !gladLoadGLLoader(SDL_GL_GetProcAddress) )
                throw std::runtime_error("Failed to initialize GLAD");

            _print_gl_info();
        }

        void _print_gl_info() const
        {
            std::cout << "Vendor          : " << glGetString( GL_VENDOR ) << std::endl
                      << "Renderer        : " << glGetString( GL_RENDERER ) << std::endl
                      << "Version         : " << glGetString( GL_VERSION ) << std::endl
                      << "Shading language: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
        }
};


// Manages SDL
struct Application
{
    public:
        Application()
        {
            // RAII
            if( SDL_Init(SDL_INIT_VIDEO) < 0)
                throw std::runtime_error("SDL could not initialize video subsystem");
        }
        ~Application()
        {
            // RAII
            SDL_Quit();
        }

        void run() 
        {
            GLWindow glwindow(640, 480);

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

                // These are related to OpenGL. So we are not doing nothing with this
                // It's just to show and understand stages of the graphic framework
                // pre_draw();
                // draw();

                glwindow.render();
            }
        }

    private:
        bool            _quit{false};
};


int main()
{ 
    try
    {
        Application app;
        app.run();
    }
    catch( const std::exception& e )
    {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }

  return 0;
}

