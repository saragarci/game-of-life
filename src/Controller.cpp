#include "Controller.h"

void Controller::getUserInput(bool &running, bool &isInitialized, int &_xMouse, int &_yMouse)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        if (e.type == SDL_KEYDOWN)
        {
            running = false;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN && !isInitialized)
        {
            _xMouse = e.motion.x;
            _yMouse = e.motion.y;
            isInitialized = true;
        }
    }
}
