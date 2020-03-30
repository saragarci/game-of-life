#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL.h>

class Controller {
public:
    void getUserInput();
    int getMousePositionX() { return _xMouse; }
    int getMousePositionY() { return _yMouse; }

private:
    int _xMouse;
    int _yMouse;
};

#endif