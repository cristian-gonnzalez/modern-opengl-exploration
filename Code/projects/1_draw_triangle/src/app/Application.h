#pragma once

#include "Renderer.h"

// Manages SDL
struct Application
{
    public:
        Application();
        ~Application();
        void run(GeometryLayout layout = GeometryLayout::SingleVBO);
    private:
        // If this is 'true' then the application terminates
        bool            _quit{false}; 
};


