#include "Grid.h"

Grid::Grid(const std::size_t screen_width,
           const std::size_t screen_height,
           const std::size_t cell_width,
           const std::size_t cell_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      cell_width(cell_width),
      cell_height(cell_height)
{
    // Initialize the video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
    
    // Create a window
    sdl_window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, 
                                  SDL_WINDOWPOS_CENTERED, screen_width, 
                                  screen_height, SDL_WINDOW_SHOWN);
    if (sdl_window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    // Create render to draw to the window
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdl_renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

Grid::~Grid()
{
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Grid::createCells()
{
    bool isActive = false;
    for (int i=0; i<Grid::getNumberOfRows(); ++i)
    {
        std::vector<Cell> v;
        for (int j=0; j<Grid::getNumberOfColumns(); ++j)
            v.emplace_back(Cell(i*cell_width, j*cell_height, static_cast<int>(cell_width), static_cast<int>(cell_height), isActive));

        _cells.emplace_back(v);
        _cellsCopy.emplace_back(v);
    }
}

void Grid::updateCells()
{
    Grid::updateCellsCopy();

    for (int i=0; i<Grid::getNumberOfRows(); ++i)
        for (int j=0; j<Grid::getNumberOfColumns(); ++j)
        {
            // Rule 1: Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if (_cellsCopy[i][j].getIsAlive() && Grid::getAliveNeighbours(i, j) < 2)
                _cells[i][j].setIsAlive(false);

            // Rule 2: Any live cell with two or three live neighbours lives on to the next generation.
            if (_cellsCopy[i][j].getIsAlive() && (Grid::getAliveNeighbours(i, j) == 2 || Grid::getAliveNeighbours(i, j) == 3))
                _cells[i][j].setIsAlive(true);       

            // Rule 3: Any live cell with more than three live neighbours dies, as if by overpopulation.
            if (_cellsCopy[i][j].getIsAlive() && Grid::getAliveNeighbours(i, j) > 3)
                _cells[i][j].setIsAlive(false);            

            // Rule 4: Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if (!_cellsCopy[i][j].getIsAlive() && Grid::getAliveNeighbours(i, j) == 3)
                _cells[i][j].setIsAlive(true);
        }
}

void Grid::updateCellsCopy()
{
    for (int i=0; i<Grid::getNumberOfRows(); ++i)
        for (int j=0; j<Grid::getNumberOfColumns(); ++j)
            _cellsCopy[i][j] = _cells[i][j];
}

// | 1 | 2 | 3 |
// | 4 | * | 5 |
// | 6 | 7 | 8 |
int Grid::getAliveNeighbours(int i, int j)
{
    Cell cell = _cellsCopy[i][j];
    int one = Grid::getNeighbour(cell.getRect()->x - 20, cell.getRect()->y - 20);
    int two = Grid::getNeighbour(cell.getRect()->x, cell.getRect()->y - 20);
    int three = Grid::getNeighbour(cell.getRect()->x + 20, cell.getRect()->y - 20);
    int four = Grid::getNeighbour(cell.getRect()->x - 20, cell.getRect()->y);
    int five = Grid::getNeighbour(cell.getRect()->x + 20, cell.getRect()->y);
    int six = Grid::getNeighbour(cell.getRect()->x - 20, cell.getRect()->y + 20);
    int seven = Grid::getNeighbour(cell.getRect()->x, cell.getRect()->y + 20);
    int eight = Grid::getNeighbour(cell.getRect()->x + 20, cell.getRect()->y + 20);
    return one + two + three + four + five + six + seven + eight;
}

int Grid::getNeighbour(int x, int y)
{
    if (x >= 0 && x < static_cast<int>(screen_width) && y >= 0 && y < static_cast<int>(screen_height))
        if (_cellsCopy[x/static_cast<int>(cell_width)][y/static_cast<int>(cell_height)].getIsAlive())
            return 1;
    return 0;
}

void Grid::drawCells()
{
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 1);
    SDL_RenderClear(sdl_renderer);

    for (auto row : _cells)
        for (auto cell : row)
            if (cell.getIsAlive()) {
                SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 1);
                SDL_RenderFillRect(sdl_renderer, cell.getRect());
            } else {
                SDL_SetRenderDrawColor(sdl_renderer, 238, 238, 238, 1);
                SDL_RenderDrawRect(sdl_renderer, cell.getRect());
            }

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Grid::setAlive(int x, int y)
{
    if (x >= 0 && x < static_cast<int>(screen_width) && y >= 0 && y < static_cast<int>(screen_height))
        _cells[x/static_cast<int>(cell_width)][y/static_cast<int>(cell_height)].setIsAlive(true);
}
