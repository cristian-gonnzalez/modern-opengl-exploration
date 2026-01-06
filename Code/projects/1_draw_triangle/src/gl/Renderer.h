#pragma once


#include <vector>
#include <string>
#include <string_view>

#include <glad/glad.h>        // glGetString

#include "GPUObject.h"


/** Renderer is pure OpenGL
 * 
 *      Owns GPU objects
 *      No SDL includes
 *      Controls draw order 
 */
class Renderer
{
    public:
        void add( const GeometryData& data );

        // Step 1: Upload geometry data (CPU → GPU)
        // Responsible for getting vertex data on the GPU
        void setup_geometry();

        // Step 2: Create and link the shader pipeline
        // Reponsible for once we have our actual geomerty creating a pipline with a vertex and a fragment
        // shaders
        void create_graphics_pipeline();

        // Step 3: Prepare frame (state + clearing)
        void pre_draw(int width, int height);
        // Step 4: Issue draw call
        void draw();

    private:        
        // ---- GPU objects ----
        // OpenGL object handles (IDs)
        std::vector<GPUObject> _gpu_objs{};
};
