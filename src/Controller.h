#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL.h>

class Controller {
public:
    void getUserInput(bool &running, bool &isInitialized, int &_xMouse, int &_yMouse);

private:

};

#endif