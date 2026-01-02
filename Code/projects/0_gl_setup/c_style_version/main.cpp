/**  Modern OpenGL
 */
#include <SDL2/SDL.h>         // SDL_init 
#include <SDL2/SDL_video.h>   // SDL_CreateWindow / SDL_GL_SetAttribute / SDL_GL_CreateContext
#include <glad/glad.h>        // glGetString
#include <iostream> 

/* 
                           Needed to call glGetString()
                          ^~~~~~~~~~~~~~~~~ ^~~~~~~~~~~~~~~~
$ g++ -std=c++17 main.cpp ./glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl
                                                                             ^~~
                                                                            dlopen
                                                          reponsable to loading symbolds at runtime        

How do we build a graphic application?

    Typically there is a few stages:

        1. Intizialize the scene
        2. Main loop:
            - Input
            - Opdates based in the input
            - Render 
                * Could be divide in multiple stages before rendering:
                  - Pre-render/ Pre-draw / Draw
        3. Cleanup

        
*/

// Globals
bool g_quit{false};

int g_screen_witdh{640};
int g_screen_height{480};
SDL_Window* g_graphics_app_window{nullptr};

// typedef void* SDL_GLContext;
//^~~~~~~~~~~ 
SDL_GLContext g_opengl_ctx{nullptr};   


void get_OpenGLInfo()
{
  std::cout << "Vendor          : " << glGetString( GL_VENDOR ) << std::endl
            << "Renderer        : " << glGetString( GL_RENDERER ) << std::endl
            << "Version         : " << glGetString( GL_VERSION ) << std::endl
            << "Shading language: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
}


void initilize()
{
  if( SDL_Init(SDL_INIT_VIDEO) < 0)
  //           ^~~~~~~~~~~~~~
  //           Video sub-sytem  
  {
    std::cerr << "SDL2 could not initialize video subsytem\n";
    exit(1);
  }

  // https://wiki.libsdl.org/SDL2/SDL_CreateWindow
  g_graphics_app_window = SDL_CreateWindow("OpenGL Window",                // title
                                           0, 0,                            // x, y, 
                                           g_screen_witdh, g_screen_height, // w, h, 
                                           SDL_WINDOW_OPENGL );             // flags 
                                  //       ^~~~~~~~~~~~~~~~~
                                  //  We have to figure out what type of windows we create and
                                  // what it is going to support
                                  // 
                                  // SDL_WINDOW_OPENGL: window usable with an OpenGL context
                                  // SDL_WINDOW_VULKAN: window usable with a Vulkan instance
                                  // SDL_WINDOW_METAL: window usable with a Metal instance

  // Note: SDL_CreateWindow/ SDL_Destroy_Window
  //    Do not forget to destroy the windows

  if( g_graphics_app_window == nullptr)
  {
    std::cerr << "SDL Windows was not able to be created\n";
    exit(1);
  }

    // Now, we set some properties to our OpenGL context

  // Set OpenGL 4.1
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  
  // We want to enforce use modern OpenGL
  //                                             Deprecated functions are disabled
  //                                               ^~~~~~~~~~~~~~~~~~~~~~~~~~~  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
             //                          ^~
             //                         24 bits

  // We need to still to setup our OpenGL Graphics context
  if( g_opengl_ctx = SDL_GL_CreateContext( g_graphics_app_window ); // Create an OpenGL context for an OpenGL window, and make it current.
      g_opengl_ctx == nullptr)
  {
    std::cerr << "OpwnGL context not available\n";
    exit(1);
  }

  // Initializes the Glad library
  if( !gladLoadGLLoader(SDL_GL_GetProcAddress) )
  {
    std::cerr << "Glad was not initialized\n";
    exit(1);
  }
  get_OpenGLInfo();

}


void input()
{
  SDL_Event e;

  while( SDL_PollEvent(&e) != 0)
  {
    if( e.type == SDL_QUIT )
    {
      std::cout << "Goodbye\n";
      g_quit = true;
    }

  }
}

void pre_draw()
{
}

void draw()
{
}

void main_loop()
{

  while( !g_quit )
  {
     input();

     // These are related to OpenGL. So we are not doing nothing with this
     // It's just to show and understand stages of the graphic framework
     // pre_draw();
     // draw();

     // Updates the screen
     SDL_GL_SwapWindow( g_graphics_app_window );

     // Note:
     //   The way that double-buffering works is when we are actually drawing a graphic scene,
     // we draw in the back buffer, and as soon as we are finished drawing, we send that information
     // to the front buffer to display. While the front is displayed to the user, we start drawing sth else in the
     // back and then we just keep flipping
  }
}

void clean_up()
{
  SDL_DestroyWindow( g_graphics_app_window );

  SDL_Quit();
}

int main()
{ 
  initilize();

  main_loop();

  clean_up();

  return 0;
}

