// g++ -std=c++20 *.cpp ./third_party/glad/src/glad.c -I. -I./third_party/glad/include -o prog -lSDL2 -ldl
#include <iostream>

#include "Application.h"

/*
Objects defined in OpenGL:

    Mesh        → geometry only (VAO/VBO)
    Shader      → compiled GPU program
    Material    → shader + uniforms
    Renderable  → mesh + material + transform
    Renderer    → owns OpenGL state & draw order
*/

int main(int argc, char** argv)
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
