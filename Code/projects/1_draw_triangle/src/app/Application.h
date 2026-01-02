#pragma once


// Manages SDL
struct Application
{
    public:
        Application();
        ~Application();
        void run();
    private:
        // If this is 'true' then the application terminates
        bool            _quit{false}; 
};


