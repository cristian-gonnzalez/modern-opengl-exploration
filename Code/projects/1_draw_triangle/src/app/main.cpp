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

int main(int argc, char** argv)
{ 
    GeometryLayout layout = GeometryLayout::SingleVBO;
    if(argc > 1)
    {
        std::string arg = argv[1];
        if (arg == "-s")
        {
            std::cout << "single VBO (positions only)\n";
        }
        else if (arg == "-i")
        {
            layout = GeometryLayout::InterleavedVBO;
            std::cout << "interleaved VBO (position + color in one VBO)\n";
        }
        else if (arg == "-m")
        {
            layout = GeometryLayout::MultipleVBOs;
            std::cout << "multiple VBOs (separate position + color buffers)\n";
        }
        else
        {
            std::cerr << "Usage: " << argv[0] << " [option]\n"
                    << "  -s → single VBO (positions only) -- default\n"
                    << "  -i → interleaved VBO (position + color in one VBO)\n"
                    << "  -m → multiple VBOs (separate position + color buffers)\n";
            return 1;
        }
    }

    try
    {
        Application app;
        app.run(layout);
    }
    catch( const std::exception& e )
    {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }

  return 0;
}
