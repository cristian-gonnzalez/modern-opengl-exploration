#pragma once


#include <vector>
#include <memory>

#include <glad/glad.h>


#include "Renderable.h"
#include "Camera.h"

/** Renderer
 *
 * Executes rendering commands using OpenGL.
 * Batches and draws Renderable objects efficiently.
 *
 * Owns no window or application logic.
 */
class Renderer
{
    public:
        // Step 3: Prepare frame (state + clearing)
        void pre_draw(const std::vector< std::shared_ptr<Renderable> >& objects, const Camera& camera, int width, int height);
        // Step 4: Issue draw call
        void draw(const std::vector< std::shared_ptr<Renderable> >& objects);
};
