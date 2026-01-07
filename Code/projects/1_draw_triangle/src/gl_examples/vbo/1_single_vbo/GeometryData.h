#pragma once

#include <vector>

#include <glad/glad.h>    

struct GeometryData
{
    static GeometryData make_triangle()
    {
        GeometryData data;
        data.vertices = {       
                            //                      y 
                            //                      ^   
                            //                      | 
                            //                      * 3
                            //                      | 
                            //                      | 
                            //        ______________|________________> x
                            //                      | 
                            //                      |
                            //            *         |        *
                            //            1         |        2
                            //      
                            //   position              vertex
                            //  x      y     z
                            -0.8f, -0.8f, 0.0f,  //   1 (Left)
                            0.8f, -0.8f, 0.0f,  //   2 (Right)
                            0.0f,  0.8f, 0.0f   //   3 (Top)
                        };
        data._num_vertex = 3;
        data._attr_size = 3;

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
        data.vertices  = {  // First triangle
                            //   position         Vertex 
                            // x      y      z
                            -0.5f, -0.5f, 0.0f,   // 1 
                             0.5f, -0.5f, 0.0f,   // 2 
                            -0.5f,  0.5f, 0.0f,   // 3 
                            // Second triangle
                            //   position         
                            // x      y      z
                             0.5f, -0.5f, 0.0f,   // 2 
                             0.5f,  0.5f, 0.0f,   // 4 
                            -0.5f,  0.5f, 0.0f,   // 3 
                        };
        data._num_vertex = 6;
        data._attr_size = 3;

        return data;
    }

    // Lives on the CPU
    std::vector<GLfloat> vertices{}; 
    //          ^~~~~~~
    //    GLfloat is defined across different architectures, they will be more
    //  uniform 
        
    // Defines the number of vertices
    std::size_t _num_vertex{3};
    // Defines the number of position components (x,y,z)
    std::size_t _attr_size{3}; 
};