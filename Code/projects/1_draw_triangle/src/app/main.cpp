// g++ -std=c++20 *.cpp ./third_party/glad/src/glad.c -I. -I./third_party/glad/include -o prog -lSDL2 -ldl
#include <iostream>

#include "Application.h"

/*
    Application
    ├─ SDL (init, quit, events)
    └─ owns GLWindow

    GLWindow (platform + context)
    ├─ SDL_Window*
    ├─ SDL_GLContext
    └─ creates graphics context

    Renderer (pure OpenGL)
    ├─ draw calls
    └─ NO SDL includes

    GPUObject (pure OpenGL) 
    ├─ shaders
    └─ VAOs / VBOs
*/

int main(int argc, char** argv)
{ 

    try
    {
        const GeometryData geo_data;

        Application app;
        app.run(geo_data);
    }
    catch( const std::exception& e )
    {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }

  return 0;
}
