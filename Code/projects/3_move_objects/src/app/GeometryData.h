#pragma once

#include <vector>

#include <glad/glad.h>    


struct Vertex
{
    public:
        std::size_t position_size() const
        {
            return sizeof(position) / sizeof(GLfloat);
        }        
        std::size_t color_size() const
        {
            return sizeof(color) / sizeof(GLfloat);
        }

        GLfloat position[3]{0.0f, 0.0f, 0.0f};
        GLfloat color[3]{0.0f, 0.0f, 0.0f};
};


/** GeometryData
 *
 * CPU-side vertex and index data container.
 * Used to construct Mesh objects.
 *
 * Has no GPU or rendering logic.
 */
struct GeometryData
{   
    public: 
        static GeometryData make_triangle()
        {
            GeometryData data{
               ._vertices = { 
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
                             { {-0.5f, -0.5f, 0.0f},   {1.0f,  0.0f, 0.0f} }, // 0 (Left)
                             { { 0.5f, -0.5f, 0.0f},   {0.0f,  1.0f, 0.0f} }, // 1 (Right)
                             { { 0.0f,  0.5f, 0.0f},   {0.0f,  0.0f, 1.0f} }  // 2 (Top)                
                            },
                            
               ._indices = { 0,1,2 } };
                            
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

            GeometryData data{
                                // Drawing in CCW order
               ._vertices  = {  // First triangle
                                //   position              color             Vertex 
                                // x      y      z
                             { {-0.5f, -0.5f, 0.0f},   {1.0f,  0.0f, 0.0f} },  // 0 
                             { { 0.5f, -0.5f, 0.0f},   {0.0f,  1.0f, 0.0f} },  // 1 
                             { {-0.5f,  0.5f, 0.0f},   {0.0f,  0.0f, 1.0f} },  // 2 
                             { { 0.5f,  0.5f, 0.0f},   {0.0f,  0.0f, 1.0f} }   // 3 
                            },
               ._indices = { 0,1,2,   // First triangle  
                            1,3,2} };  // Second triangle
                            
            return data;
        }
    
    
        std::vector<Vertex>  vertices() const
        {
            return _vertices;
        }
        std::vector<GLuint>  indices() const
        {
            return _indices;
        }
        std::size_t vertices_size() const
        {
            return _vertices.size();
        }  
        std::size_t indices_size() const
        {
            return _indices.size();
        }  
        std::size_t position_size() const 
        {
            return _vertices.at(0).position_size();
        }
        std::size_t color_size() const
        {
            return _vertices.at(0).color_size();
        }

        // ----- CPU data ------
        std::vector<Vertex>  _vertices{};
        std::vector<GLuint>  _indices{};
};