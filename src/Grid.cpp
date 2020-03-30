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
    }
}

void Grid::updateCells()
{
    std::vector<std::vector<Cell>> cellsPresentState = createCellsCopy();

    for (int i=0; i<Grid::getNumberOfRows(); ++i)
        for (int j=0; j<Grid::getNumberOfColumns(); ++j)
        {
            //std::cout << "**** Index: " << i << ", " << j << " cell is: " << cellsPresentState[i][j].getRect()->x << ", " << cellsPresentState[i][j].getRect()->y << std::endl;

            //Cell presentCell = cellsPresentState[i][j];

            // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if (cellsPresentState[i][j].getIsAlive() && getAliveNeighbours(i, j, cellsPresentState) < 2)
                _cells[i][j].setIsAlive(false);

            // Any live cell with two or three live neighbours lives on to the next generation.
            if (cellsPresentState[i][j].getIsAlive() && (getAliveNeighbours(i, j, cellsPresentState) == 2 || getAliveNeighbours(i, j, cellsPresentState) == 3))
                _cells[i][j].setIsAlive(true);       

            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            if (cellsPresentState[i][j].getIsAlive() && getAliveNeighbours(i, j, cellsPresentState) > 3)
                _cells[i][j].setIsAlive(false);            

            // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if (!cellsPresentState[i][j].getIsAlive() && getAliveNeighbours(i, j, cellsPresentState) == 3)
                _cells[i][j].setIsAlive(true);   


            /*
            // Rule 1: Any live cell with two or three neighbors survives.
            if (cellsPresentState[i][j].getIsAlive() && (getAliveNeighbours(cellsPresentState[i][j]) == 2 || getAliveNeighbours(cellsPresentState[i][j]) == 3))
                _cells[i][j].setIsAlive(true);
            
            // Rule 2: Any dead cell with three live neighbors becomes a live cell.
            else if (!cellsPresentState[i][j].getIsAlive() && getAliveNeighbours(cellsPresentState[i][j]) == 3)
                _cells[i][j].setIsAlive(true);

            // Rule 3: All other live cells die in the next generation. Similarly, all other dead cells stay dead.
            else if (cellsPresentState[i][j].getIsAlive())
                _cells[i][j].setIsAlive(false);
            */
        }
}

std::vector<std::vector<Cell>> Grid::createCellsCopy()
{
    std::vector<std::vector<Cell>> cellsCopy;
    for (int i=0; i<Grid::getNumberOfRows(); ++i)
    {
        std::vector<Cell> v;
        for (int j=0; j<Grid::getNumberOfColumns(); ++j)
            v.emplace_back(Cell(_cells[i][j].getRect()->x, _cells[i][j].getRect()->y, _cells[i][j].getRect()->w, _cells[i][j].getRect()->h, _cells[i][j].getIsAlive()));

        cellsCopy.emplace_back(v);
    }
    return cellsCopy;
}

// | 1 | 2 | 3 |
// | 4 | * | 5 |
// | 6 | 7 | 8 |
int Grid::getAliveNeighbours(int i, int j, std::vector<std::vector<Cell>> cellsPresentState)
{
    Cell cell = cellsPresentState[i][j];
    int one = getNeighbour(cell.getRect()->x - 20, cell.getRect()->y - 20, cellsPresentState);
    int two = getNeighbour(cell.getRect()->x, cell.getRect()->y - 20, cellsPresentState);
    int three = getNeighbour(cell.getRect()->x + 20, cell.getRect()->y - 20, cellsPresentState);
    int four = getNeighbour(cell.getRect()->x - 20, cell.getRect()->y, cellsPresentState);
    int five = getNeighbour(cell.getRect()->x + 20, cell.getRect()->y, cellsPresentState);
    int six = getNeighbour(cell.getRect()->x - 20, cell.getRect()->y + 20, cellsPresentState);
    int seven = getNeighbour(cell.getRect()->x, cell.getRect()->y + 20, cellsPresentState);
    int eight = getNeighbour(cell.getRect()->x + 20, cell.getRect()->y + 20, cellsPresentState);
    int result = one + two + three + four + five + six + seven + eight;
    /*std::cout << "**** Neighbours of the cell: " << cell.getRect()->x << ", " << cell.getRect()->y << "are..."<< std::endl;
    std::cout << "1: " << one << std::endl;
    std::cout << "2: " << two << std::endl;
    std::cout << "3: " << three << std::endl;
    std::cout << "4: " << four << std::endl;
    std::cout << "5: " << five << std::endl;
    std::cout << "6: " << six << std::endl;
    std::cout << "7: " << seven << std::endl;
    std::cout << "8: " << eight << std::endl;*/
    return result;
}

int Grid::getNeighbour(int x, int y, std::vector<std::vector<Cell>> cellsPresentState)
{
    if (x >= 0 && x < static_cast<int>(screen_width) && y >= 0 && y < static_cast<int>(screen_height))
        if (cellsPresentState[x/static_cast<int>(cell_width)][y/static_cast<int>(cell_height)].getIsAlive())
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
                SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 1);
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
    std::cout << "Cell x: " << x << " y: " << y << std::endl;
    if (x >= 0 && x < static_cast<int>(screen_width) && y >= 0 && y < static_cast<int>(screen_height))
        _cells[x/static_cast<int>(cell_width)][y/static_cast<int>(cell_height)].setIsAlive(true);
    else
        std::cout << "Cell out of bounds!" << y << std::endl;
}
