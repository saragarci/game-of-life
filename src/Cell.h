#ifndef CELL_H
#define CELL_H

#include <SDL.h>

class Cell {
public:
    Cell(int x, int y, int w, int h, bool isAlive);
    SDL_Rect *getRect() { return &_rect; }
    void live();
    void die();
    bool isAlive() { return _isAlive; }

private:
    bool _isAlive;
    SDL_Rect _rect;
};

#endif
