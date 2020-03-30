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
        else if (e.type == SDL_MOUSEBUTTONDOWN && !isInitialized)
        {
            _xMouse = e.motion.x;
            _yMouse = e.motion.y;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_RETURN) {
                isInitialized = true;
            }
        }
    }
}
