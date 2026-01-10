#pragma once

#include <glm/ext/matrix_transform.hpp>

/** Transform
 *
 * Stores local spatial data (position, rotation, scale).
 * Produces a model matrix for rendering.
 *
 * Pure CPU-side math, no OpenGL dependencies.
 */
struct Transform 
{    
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
