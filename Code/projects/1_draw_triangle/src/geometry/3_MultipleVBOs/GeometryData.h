#pragma once

#include <vector>

#include <glad/glad.h>    

struct GeometryData
{
    //                      y 
    //                      ^   
    //                      | 
    //                    3 * blue
    //                      | 
    //                      | 
    //        ______________|________________x
    //                      | 
    //                      |
    //            *         |        *
    //            1         |        2
    //           red                green
    const std::vector<GLfloat> vertices{ 
                                          //   position              vertex
                                          //  x      y     z
                                           -0.8f, -0.8f, 0.0f,  // 1 (Left)
                                            0.8f, -0.8f, 0.0f,  // 2 (Right)
                                            0.0f,  0.8f, 0.0f   // 3 (Top)
                                        };

    const std::vector<GLfloat> colors{    //   position              vertex
                                          //  r      g     b
                                            1.0f,  0.0f, 0.0f,  // 1 (Left)  red
                                            0.0f,  1.0f, 0.0f,  // 2 (Right) green 
                                            0.0f,  0.0f, 1.0f   // 3 (Top)   blue
                                        };

    // Defines the number of vertices
    const std::size_t _num_vertex{3};
    // Defines the number of position components (x,y,z)
    const std::size_t _attr_size{3}; 
    
    const std::size_t _color_nums{3}; 
    
};