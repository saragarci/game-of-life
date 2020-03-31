# Game Of Life

This application is a representation of the Game Of Life.

**About the game**

The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970.
The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

**Rules**

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed; births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations.

## Usage

### Dependencies

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

### Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./GameOfLife`.

### Starting the game

After running `./GameOfLife` the user needs to create an initial pattern in order to see how it evolves. For this, follow the next steps:
1. On the window that will open up, choose the cells you want to activate by clicking on them using your mouse. The cells that you activate will end up being the initial pattern. In the [Examples of patterns section from the Wikipedia](https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Examples_of_patterns) you can find examples of initial patters that you may want to try.
2. Once you are done, press enter to start the game and see how the pattern evolves with each iteration.
3. To stop the game, simply close the window.

## Credits

### Used resources

* [Wikipedia Game of Life](https://en.wikipedia.org/wiki/Conway's_Game_of_Life)
* [Patterns of the Game of life](game-of-life.daneaiulian.com)
* [SDL Wiki](https://wiki.libsdl.org/APIByCategory)

### Contributors

* [Sara Garci](s@saragarci.com)

## License

© Copyright 2020 by Sara Garci. All rights reserved.
