/** OpenGL Objects, Context (through Mesa), and State Machine
 * Modern OpenGL
 */

/*

OpenGL Objects
    OpenGL is a c-based API. This means that objects are not the same as C++ objects or OOP way.

    These are just c-structs treated as piece of data (usually called context) and we need separate functions to manipulate them. For ex:

struct gl_context {
    .....
};

GLBoolean _gl_context_initialize(struct gl_context* ctx);
void _gl_context_release(struct gl_context* ctx);

    When we run our GL setup, we see Mesa

$ ./prog 
Vendor          : Mesa
Renderer        : llvmpipe (LLVM 20.1.2, 256 bits)
Version         : 4.5 (Core Profile) Mesa 25.0.7-0ubuntu0.24.04.2
Shading language: 4.50
Goodbye

  Mesa is an open source implementation of OpenGL (https://gitlab.freedesktop.org/mesa/mesa), Here we can see example how OpenGL objects are defined



GLContext:
    GL context is an state machine so the object gl_context manages our state. The sate means the gphracis pipeline stages


We can see how this context are populate during the different stages: https://webglfundamentals.org/webgl/lessons/resources/webgl-state-diagram.html?exampleId=triangle#no-help



*/