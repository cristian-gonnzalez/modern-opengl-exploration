#pragma once

#include <vector>

#include <glad/glad.h>    

struct GeometryData
{    
    static GeometryData make_triangle()
    {
        GeometryData data;
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
        
        // Drawing in CCW order
        data.vertices  = { 
                            //   position              vertex
                            //  x      y     z
                            -0.8f, -0.8f, 0.0f,  // 1 (Left)
                            0.8f, -0.8f, 0.0f,  // 2 (Right)
                            0.0f,  0.8f, 0.0f   // 3 (Top)
                        };
        data.colors = {    //   position              vertex
                        //  r      g     b
                        1.0f,  0.0f, 0.0f,  // 1 (Left)  red
                        0.0f,  1.0f, 0.0f,  // 2 (Right) green 
                        0.0f,  0.0f, 1.0f   // 3 (Top)   blue
                    };
        
        data._num_vertex = 3;
        data._attr_size = 3;
        data._color_nums = 3;

        

        return data;
    }

    static GeometryData make_quad()
    {    
        //                     y
        //                     ^
        //            3        |         4 
        //            *-----------------*
        //            | \      |        |
        //            |   \    |        |
        //            |     \  |        |
        //            |       \|        |
        //  ──────────|────────|─────────|─────────> x
        //            |        |\       |
        //            |        |  \     |
        //            |        |    \   |
        //            |        |      \ |
        //            *--------|--------*
        //            1        |        2

        GeometryData data;

        // Drawing in CCW order
        data.vertices  = {  // First triangle
                            //   position              color             Vertex 
                            // x      y      z
                            -0.5f, -0.5f, 0.0f,      // 1 
                             0.5f, -0.5f, 0.0f,      // 2 
                            -0.5f,  0.5f, 0.0f,      // 3 
                            // Second triangle
                            //   position              color
                            // x      y      z
                             0.5f, -0.5f, 0.0f,     // 2 
                             0.5f,  0.5f, 0.0f,     // 4 
                            -0.5f,  0.5f, 0.0f,      // 3 
                        };
        data.colors = {
            1.0f,  0.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
            0.0f,  0.0f, 1.0f,

            0.0f,  1.0f, 0.0f,
            0.0f,  0.0f, 1.0f, 
            0.0f,  0.0f, 1.0f  
        };
                        
        data._num_vertex = 6;
        data._attr_size = 3;
        data._color_nums = 3;

        return data;
    }

    std::vector<GLfloat> vertices{};
    std::vector<GLfloat> colors{};

    // Defines the number of vertices
    std::size_t _num_vertex{3};
    // Defines the number of position components (x,y,z)
    std::size_t _attr_size{3}; 
    std::size_t _color_nums{3}; 
    
};