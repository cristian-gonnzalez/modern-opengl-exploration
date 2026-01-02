#pragma once

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
        GLWindow(int width=640, int height=480);
        ~GLWindow();

        void render();
    
        int width() const { return _width; }
        int height() const { return _height; }

    private:
        SDL_Window*   _window{nullptr};
        SDL_GLContext _gl_ctx{nullptr};
        int           _width{640}; 
        int           _height{480};

        void _create_gl_contex();
        void _print_gl_info() const;
};
