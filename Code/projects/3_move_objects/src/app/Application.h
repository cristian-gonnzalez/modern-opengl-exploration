#pragma once

#include "Renderer.h"
#include "GeometryData.h"


/** Application manages SDL
 * 
 *      Initializes SDL
 *      Owns event loop
 *      Does not touch OpenGL directly  
 */
struct Application
{
    public:
        Application();
        ~Application();
        void run(const GeometryData& geo_data);
    private:
        // If this is 'true' then the application terminates
        bool            _quit{false}; 

        void read_input(Transform& transform);
};


