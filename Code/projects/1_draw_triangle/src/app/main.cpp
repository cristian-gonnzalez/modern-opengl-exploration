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
    ├─ shaders
    ├─ VAOs / VBOs
    ├─ draw calls
    └─ NO SDL includes
*/

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
