/** GLM (OpenGL Mathematics)
 */
#include <iostream>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

#include <glm/ext/matrix_clip_space.hpp> // glm::perspective

#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <glm/gtx/string_cast.hpp>


// See: https://learnopengl.com/Getting-started/Transformations
//
// Coordinate System (OpenGL default)
//
//          y
//          ^
//          |
//          |
//          |
//          *------------------------> x
//         /
//        /
//       z
//
// Right-handed coordinate system
//

void print_matrix(const glm::mat4& model)
{
    // Trick to print each column
    for(size_t i=0; i<4; ++i)
        std::cout << glm::to_string( model[i] ) << std::endl;     
}

int main()
{
    
    //              y
    //                ^
    //  (1,5,1,1)   * |
    //                |
    //                |
    //                *------------------------> x
    //              /
    //             /
    //           z
    //
    //
    // Create a 'vertex' (i.e. point) 
    // 'This is the "local coordinates"' 
    glm::vec4 vertex(1.0f, 5.0f, 1.0f, 1.0f);
    //                                  ^~~~
    //                            This is the 'w' coordinate. 
    //
    //  w=1 means we have a position (point)
    //  w=0 means we have a vector (magnitud and direction)
    //
    // w is important to deteminate if we want a 'point' or 'vector'  
    //
    //
    //              y    * (1,5,-3,1)                  point  +    point   =  nonsense  
    //                ^                                point  -    point   =  vector   
    //  (1,5,1,1)   * |                             (1,5,1,1) - (1,5,-3,1) = (0,0,-4,0)                      
    //                |                                                              ^
    //                |                                                           vector          
    //                *------------------------> x     vector - vector =  vector 
    //              /
    //             /
    //           z


    //   Create a model matrix for our geometry. A model is what we actually want
    // to do or how we want to transform this point (translate it, rotate it, scale it)
    //
    //   We move from: 'local space' -> 'world space'
    //
    //
    // NOTE: Do not count on GLW to provide you an identity matrix
    glm::mat4 model(1.0f);
    //   ^~~~       ^~~~
    // Matrx 4x4    Initialize with '1' for identity matrix
    //   
    //  [ 1  0  0  0 ]
    //  [ 0  1  0  0 ]   Identity matrix
    //  [ 0  0  1  0 ]
    //  [ 0  0  0  1 ]

    // The idea is to take the identity matrix and multiply it by the point so  
    //                 fil * col
    //                (1*1 + 0*5 + 0*1 + 0*1)
    //                            ^
    //  [ 1  0  0  0 ]   [1]    [ 1 ]
    //  [ 0  1  0  0 ] * [5] =  [ 5 ] 
    //  [ 0  0  1  0 ]   [1]    [ 1 ]
    //  [ 0  0  0  1 ]   [1]    [ 1 ]
    //                    ^       ^
    //              world space   |
    //                           new location
    //

    // Perfom some transformation (i.e. moving us in the world)
    // We are not in 'world space'

    // Scaling Matrix
    model = glm::scale( glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f) );
                                              //   ^~~~  ^~~~  ^~~~
                                              //     x     y     z
                                              //  Doubling my coordinates

    // This model allows us to double 
    print_matrix(model);                    // vec4(2.000000, 0.000000, 0.000000, 0.000000)
                                            // vec4(0.000000, 2.000000, 0.000000, 0.000000)
                                            // vec4(0.000000, 0.000000, 2.000000, 0.000000)
                                            // vec4(0.000000, 0.000000, 0.000000, 1.000000)
    
    // Now we apply our 'model' matrix to the vertex
    glm::vec4 worldspace_vertex = (model * vertex);
    std::cout << glm::to_string( worldspace_vertex ) << std::endl; // vec4(2.000000, 10.000000, 2.000000, 1.000000)
    // So, by scaling, we moves the vertex
    

    //       (2,10,2,1) * new position
    //                  | 
    //              y   |              
    //                ^ |                           
    //     (1,5,1,1) *| |                                         
    //                | |                                               
    //                | |                                                  
    //                *-|-----------------------> x  
    //              / |/| /    
    //             /    |/
    //           z


    return 0;
}
