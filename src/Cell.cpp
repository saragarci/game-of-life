#include "Cell.h"

Cell::Cell(int x, int y, int w, int h, bool isAlive) 
    : _rect{x, y, w, h}, _isAlive(isAlive) {}

void Cell::live() {
    _isAlive = true;
}
    
void Cell::die() {
    _isAlive = false;
}