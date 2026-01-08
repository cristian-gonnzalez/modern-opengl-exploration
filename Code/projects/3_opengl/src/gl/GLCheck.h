#pragma once

/*
Usage:

GL_CHECK( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
GL_CHECK( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );

*/

// Uncomment this to use GL_CHECK macro
//#define DEBUG

#ifdef DEBUG
#include <iostream>
    #define GL_CHECK(stmt)                         \
        do {                                       \
            stmt;                                  \
            GLenum err;                            \
            while ((err = glGetError()) != GL_NO_ERROR) { \
                std::cerr << "OpenGL error " << err       \
                        << " at " << __FILE__             \
                        << ":" << __LINE__                \
                        << std::endl;                     \
                char i;                                   \
                std::cin >> i;                            \
            }                                             \
        } while (0)
#else
    #define GL_CHECK(stmt) stmt
#endif
