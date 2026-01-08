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

    //   Create a model matrix for our geometry.
    glm::mat4 model(1.0f);
    
    // Perfom some transformation (i.e. moving us in the world)
    // We are not in 'world space'

    // Rotatin Matrix
    model = glm::rotate( glm::mat4(1.0f), 
                         glm::radians(180.0f),   // The angle we want to rotate
                         glm::vec3(0, 1, 0) );   // Determinate the axis over we wanto to rotate
                        //         ^  ^  ^
                        //         x  y  z                
                        //            |
                        //         rotate over the y-axis

    // This model allows us to double 
    print_matrix(model);                    // vec4(-1.000000, 0.000000,  0.000000, 0.000000)
                                            // vec4( 0.000000, 1.000000,  0.000000, 0.000000)
                                            // vec4(-0.000000, 0.000000, -1.000000, 0.000000)
                                            // vec4( 0.000000, 0.000000,  0.000000, 1.000000)
    
    // Now we apply our 'model' matrix to the vertex
    glm::vec4 worldspace_vertex = (model * vertex);
    std::cout << glm::to_string( worldspace_vertex ) << std::endl; // vec4(-1.000000, 5.000000, -1.000000, 1.000000)
    // So, by scaling, we moves the vertex
    
    //                y
    //                ^ 
    //  (-1,5,-1,1) * |
    //              | |                    
    //              | |                            
    //              | * (1,5,1,1)                                          
    //              | |                                                
    //              / |                                                  
    //  ---------------------------------------> x  
    //              / |/    
    //             /    
    //           z


    return 0;
}
