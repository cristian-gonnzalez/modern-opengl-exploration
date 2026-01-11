#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

/** Transform
 *
 * Stores local spatial data (position, rotation, scale).
 * Produces a model matrix for rendering.
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
        model = glm::translate( model, position );             

        return model;
    }

    glm::vec3 position{0};
};
