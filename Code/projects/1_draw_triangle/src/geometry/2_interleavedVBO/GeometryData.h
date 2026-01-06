#pragma once

#include <vector>

#include <glad/glad.h>    

struct GeometryData
{
    // Lives on the CPU
    //    GLfloat is defined across different architectures, they will be more
    //  uniform 
    //                ^~~~~~~
    const std::vector<GLfloat> vertices{ 
                                            //                      y 
                                            //                      ^   
                                            //                      | 
                                            //                      * blue
                                            //                      | 
                                            //                      | 
                                            //        ______________|________________x
                                            //                      | 
                                            //                      |
                                            //            *         |        *
                                            //            1         |        2
                                            //           red                green
                                            
                                            //   position              color             vertex  
                                            // x      y      z      r      g     b
                                            -0.8f, -0.8f, 0.0f,   1.0f,  0.0f, 0.0f,  // 1 (Left)
                                             0.8f, -0.8f, 0.0f,   0.0f,  1.0f, 0.0f,  // 2 (Right)
                                             0.0f,  0.8f, 0.0f,   0.0f,  0.0f, 1.0f   // 3 (Top)                
                                        };
    // Defines the number of vertices
    const std::size_t _num_vertex{3};
    // Defines the number of position components (x,y,z)
    const std::size_t _position_size{3}; 
    const std::size_t _color_size{3}; 
};