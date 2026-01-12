#pragma once

#include <SDL2/SDL.h>         // SDL_init 
#include <SDL2/SDL_video.h>   // SDL_CreateWindow / SDL_GL_SetAttribute / SDL_GL_CreateContext
#include <glad/glad.h>        // glGetString

#include <iostream>
#include <stdexcept>
#include <utility>


/** GW Window manages the Window + GL context
 *
 *      Creates window
 *      Creates GL context
 *      Initializes GLAD
 *      Swaps buffers
 */ 
class GLWindow
{
    public:
        GLWindow(int width=640, int height=480);
        ~GLWindow();

        GLWindow(const GLWindow&) = delete;
        GLWindow operator=(const GLWindow&) = delete;
        
        GLWindow(const GLWindow&&) = delete;
        GLWindow operator=(GLWindow&&) = delete;

        void render();
    
        int width() const { return _width; }
        int height() const { return _height; }

         SDL_Window* get_window()
         {
            return _window;
         }

    private:
        SDL_Window*   _window{nullptr};  // Rule of 3
        SDL_GLContext _gl_ctx{nullptr};
        int           _width{640}; 
        int           _height{480};

        void _create_gl_contex();
        void _print_gl_info() const;
};
