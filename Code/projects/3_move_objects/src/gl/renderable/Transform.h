#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

/** Transform
 *
 * Stores local spatial data (position, rotation, scale).
 * Produces a model matrix for rendering. This not produce the action.
 * Then we will to share the matrix using uniforms to the shaders
 *
 * Pure CPU-side math, no OpenGL dependencies.
 */
struct Transform 
{    
    // This is our model transdormation by translating
    // our object into world space
    glm::mat4 get_model_matrix() const 
    {
        //      unit matrix   
        //       ^~~~~~~~~~~~~~   
        glm::mat4 model(1.0f);

        // NOTE: 
        //   Transformation order matters
        //
        //         [translate -> rotate -> scale]   !=   [rotate -> translate -> scale]
        //

        // Set our model matrix by applyitng a translation (moving the object)
        model = glm::translate( model, position );  
        // Update our model matrix by applying a rotation after a translation   
        model = glm::rotate( model, 
                             glm::radians(rotation.y),       // angle
                             glm::vec3(0.0f, 1.0f, 0.0f) );  // the axis we want to rotate around     
                                    // ^~~~  ^~~~  ^~~~
                                    //   x     y     z
        model = glm::rotate( model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f) );       
        model = glm::rotate( model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f) );                                       
        model = glm::scale( model, scale );
        
        return model;
    }

    void reset()
    {
        rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
        position =  glm::vec3(0.0f, 0.0f, -5.0f);
    }

    glm::vec3 rotation{0};
    glm::vec3 position{0,0,-5};
    glm::vec3 scale{1};
};
