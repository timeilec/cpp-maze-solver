#include <iostream>
#include <vector>
#include <string>

class Cell
{
public:
    void SetVisited(bool value) { visited = value; }
    bool GetVisited() const { return visited; }
    void SetSolveRoute(bool value) { solveRoute = value; }
    bool GetSolveRoute() const { return solveRoute; }
    void SetWall(int wallPosition, int value) { walls.at(wallPosition) = value; }
    std::vector<bool> GetWalls() const { return walls; }
    void SetNeighbour(int position, int value) { neighbours.at(position) = value; }
    std::vector<bool> GetNeighbours() const { return neighbours; }

private:
    bool visited = false;
    bool solveRoute = false;
    std::vector<bool> walls = {true, true, true, true};    // right, up, left, down
    std::vector<bool> neighbours = {true, true};    // right, lower
};

class Maze
{
public:
    void PrintMaze() const;
    void InitialiseMaze();
    bool ValidMove(std::vector<int> coordinates);
    bool HasValidMoves(std::vector<int> coordinates);
    bool SolveMaze(std::vector<std::vector<int>> &cellsStack, std::vector<std::vector<int>> &solveRoute, int cellsVisited, int cellsToVisit);
    void GenerateMaze(int numRows, int numColumns);
    void SetVisited(std::vector<int> coordinates, bool value) { maze.at(coordinates.at(0)).at(coordinates.at(1)).SetVisited(value); }
    bool GetVisited(std::vector<int> coordinates) const { return maze.at(coordinates.at(0)).at(coordinates.at(1)).GetVisited(); }
    void SetSolveRoute(std::vector<int> coordinates, bool value) { maze.at(coordinates.at(0)).at(coordinates.at(1)).SetSolveRoute(value); }
    bool GetSolveRoute(std::vector<int> coordinates) const { return maze.at(coordinates.at(0)).at(coordinates.at(1)).GetSolveRoute(); }
    void SetWall(std::vector<int> coordinates, int wallPosition, bool value) { maze.at(coordinates.at(0)).at(coordinates.at(1)).SetWall(wallPosition, value); }

private:
    std::vector<std::vector<Cell>> maze;
    int numRows;
    int numColumns;
};

void Maze::PrintMaze() const
{
    int numColumns = maze.size();
    int numRows = maze.at(0).size();
    for (int j = 0; j < numRows; ++j)
    {
        for (int i = 0; i < numColumns; ++i)    // Top row of cell output
        {
            std::vector<bool> walls =  maze.at(i).at(j).GetWalls();  // right, up, left, down
            std::cout << "+";
            if (walls.at(1)) { std::cout << "---"; } else { std::cout << "   "; }
            if (maze.at(i).at(j).GetNeighbours().at(0) == false)   // no neighbour to the right
            {
                std::cout << "+";
            }
        }

        std::cout << std::endl;

        for (int i = 0; i < numColumns; ++i)    // Middle row of cell output
        {
            std::vector<bool> walls =  maze.at(i).at(j).GetWalls();  // right, up, left, down
            if (walls.at(2)) { std::cout << "|"; } else { std::cout << " "; }
            if (maze.at(i).at(j).GetSolveRoute()) { std::cout << " . "; } else { std::cout << "   "; }
            if (maze.at(i).at(j).GetNeighbours().at(0) == false)   // no neighbour to the right
            {
                if (walls.at(0)) { std::cout << "|"; } else { std::cout << " "; }
            }
        }

        std::cout << std::endl;
        
        for (int i = 0; i < numColumns; ++i)    // Bottom row of cell output
        {
            std::vector<bool> walls =  maze.at(i).at(j).GetWalls(); // right, up, left, down
            if (maze.at(i).at(j).GetNeighbours().at(1) == false)   // no neighbour below
            {
                std::cout << "+";
                if (walls.at(3)) { std::cout << "---"; } else { std::cout << "   "; }
                if (maze.at(i).at(j).GetNeighbours().at(0) == false)   // no neighbour to the right
                {
                    std::cout << "+";
                }
            }
        }

    }
}

void Maze::InitialiseMaze()
{
    maze.resize(numColumns);
    for (int i = 0; i < numColumns; ++i)
    {
        maze.at(i).resize(numRows);
        maze.at(i).at(numRows-1).SetNeighbour(1,false); // No neighbour below on bottom row
    }
    for (int i = 0; i < numRows; ++i)
    {
        maze.at(numColumns-1).at(i).SetNeighbour(0,false);  // No neighbour on right of last column
    }
}

bool Maze::ValidMove(std::vector<int> coordinates)
{
    int x = coordinates.at(0);
    int y = coordinates.at(1);

    // On the board
    if (x < 0) { return false; }
    if (x >= numColumns) { return false; }
    if (y < 0) { return false; }
    if (y >= numRows) { return false; }

    // Not visited yet
    bool visited = GetVisited(coordinates);
    if (visited) { return false; }

    return true;
}

bool Maze::HasValidMoves(std::vector<int> coordinates)
{
    int x = coordinates.at(0);
    int y = coordinates.at(1);
    bool rightValid = true;
    bool upValid = true;
    bool leftValid = true;
    bool downValid = true;

    // Cell to the right
    if (x+1 < 0) { rightValid = false; }
    if (x+1 >= numColumns) { rightValid = false; }
    if (y < 0) { rightValid = false; }
    if (y >= numRows) { rightValid = false; }
    if (rightValid)
    {
        if ( GetVisited({x+1, y}) ) { rightValid = false; }
    }


    // Cell above
    if (x < 0) { upValid = false; }
    if (x >= numColumns) { upValid = false; }
    if (y-1 < 0) { upValid = false; }
    if (y-1 >= numRows) { upValid = false; }
    if (upValid)
    {
        if ( GetVisited({x, y-1}) ) { upValid = false; }
    }

    // Cell to the left
    if (x-1 < 0) { leftValid = false; }
    if (x-1 >= numColumns) { leftValid = false; }
    if (y < 0) { leftValid = false; }
    if (y >= numRows) { leftValid = false; }
    if (leftValid)
    {
        if ( GetVisited({x-1, y}) ) { leftValid = false; }
    }

    // Cell below
    if (x < 0) { downValid = false; }
    if (x >= numColumns) { downValid = false; }
    if (y+1 < 0) { downValid = false; }
    if (y+1 >= numRows) { downValid = false; }
    if (downValid)
    {
        if ( GetVisited({x, y+1}) ) { downValid = false; }
    }

    // IF FOR RETURNS
    if (rightValid || upValid || leftValid || downValid) { return true; } else { return false; }
}

bool Maze::SolveMaze(std::vector<std::vector<int>> &cellsStack, std::vector<std::vector<int>> &solveRoute, int cellsVisited, int cellsToVisit)
{
    int newX;
    int newY;
    int moveDirection;
    int newCoordWall;
    bool done;
    std::vector<int> currentCoordinates = cellsStack.back();
    std::vector<int> newCoordinates;

    // Base case
    if (cellsVisited == cellsToVisit)
    {
        return true;
    }

    if (((currentCoordinates.at(0) == numColumns-1) && (currentCoordinates.at(1) == numRows-1)) && (solveRoute.size() == 0))
    {
        solveRoute = cellsStack;
    }

    while (!done)
    {
        currentCoordinates = cellsStack.back();
        moveDirection = rand() % 4;
        if (HasValidMoves(currentCoordinates))
        {
            switch (moveDirection)
            {
            case 0: // right
                newCoordinates = {currentCoordinates.at(0) + 1, currentCoordinates.at(1) + 0};
                newCoordWall = 2;
                break;
            case 1: // up
                newCoordinates = {currentCoordinates.at(0) + 0, currentCoordinates.at(1) - 1};
                newCoordWall = 3;
                break;
            case 2: // left
                newCoordinates = {currentCoordinates.at(0) - 1, currentCoordinates.at(1) + 0};
                newCoordWall = 0;
                break;
            case 3: // down
                newCoordinates = {currentCoordinates.at(0) + 0, currentCoordinates.at(1) + 1};
                newCoordWall = 1;
                break;
            }

            if (ValidMove(newCoordinates)) // Move to new VALID square (on board, not visited)
            {
                // Visit
                SetWall(currentCoordinates, moveDirection, false);  // right, up, left, down
                SetWall(newCoordinates, newCoordWall, false);  // right, up, left, down
                SetVisited(newCoordinates, true);
                cellsStack.push_back(newCoordinates);
                cellsVisited++;

                // Recursion
                done = SolveMaze(cellsStack, solveRoute, cellsVisited, cellsToVisit);
                if (done)
                {
                    return true;
                }

                // Remove visit
                SetVisited(newCoordinates, false);
                cellsStack.pop_back();
                cellsVisited--;
            }
        }
        else
        {
            cellsStack.pop_back();
        }
    }
    return false;
}

void Maze::GenerateMaze(int numRows, int numColumns)
{
    this->numRows = numRows;
    this->numColumns = numColumns;

    InitialiseMaze();

    // Create empty maze and then make a solve route
    std::vector<std::vector<int>> cellsStack;
    std::vector<std::vector<int>> solveRoute;
    cellsStack.push_back({0,0});
    SetVisited({0,0}, true);
    int cellsVisited = cellsStack.size();
    int cellsToVisit = numRows * numColumns;
    SolveMaze(cellsStack, solveRoute, cellsVisited, cellsToVisit);
    for (int i = 0; i < solveRoute.size(); ++i)
    {
        SetSolveRoute(solveRoute.at(i), true);
    }
}

int main(int argc, char *argv[])
{
    try
    {
        Maze maze;
        if (argc == 3)
        {
            // Random generation
            int numRows = std::stoi(argv[1]);
            int numColumns = std::stoi(argv[2]);
            if (numRows <= 0 || numColumns <= 0)
            {
                throw std::runtime_error("invalid number of rows/columns");
            }

            srand(time(0));
            maze.GenerateMaze(numRows, numColumns);
            maze.PrintMaze();
        }
        else if (argc == 4)
        {
            // Seed generation
            int numRows = std::stoi(argv[1]);
            int numColumns = std::stoi(argv[2]);
            int seed = std::stoi(argv[3]);
            if (numRows <= 0 || numColumns <= 0)
            {
                throw std::runtime_error("invalid number of rows/columns");
            }

            srand(seed);
            maze.GenerateMaze(numRows, numColumns);
            maze.PrintMaze();
        }
        else
        {
            throw std::runtime_error("invalid parameter list");
        }
    }
    catch (std::logic_error &e)
    {
        std::cerr << e.what();
        return 1;
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}