#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <cstdlib>
#include <ctime>

Model::Model() : 
    modelListener(0),
    currentType(Tetris::NONE),
    nextType(Tetris::NONE),
    tickCounter(0),
    dropSpeed(60) // Assuming 60Hz tick, drop every 1 second
{
    // Initialize grid
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            grid[y][x] = -1;
        }
    }

    // Seed random (simple approach for now)
    srand(static_cast<unsigned int>(time(NULL)));

    // Generate initial next piece and spawn first
    nextType = getRandomPiece();
    spawnPiece();
}

void Model::tick()
{
    tickCounter++;
    if (tickCounter >= dropSpeed)
    {
        tickCounter = 0;
        step();
    }

    if (modelListener != 0)
    {
        modelListener->modelStateChanged();
    }
}

void Model::moveLeft()
{
    if (!isCollision(currentX - 1, currentY, currentRotation))
    {
        currentX--;
    }
}

void Model::moveRight()
{
    if (!isCollision(currentX + 1, currentY, currentRotation))
    {
        currentX++;
    }
}

void Model::rotate()
{
    int nextRotation = (currentRotation + 1) % 4;
    if (!isCollision(currentX, currentY, nextRotation))
    {
        currentRotation = nextRotation;
    }
}

void Model::step()
{
    if (!isCollision(currentX, currentY + 1, currentRotation))
    {
        currentY++;
    }
    else
    {
        lockPiece();
    }
}

void Model::lockPiece()
{
    // Copy falling piece into grid
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (Tetris::SHAPES[currentType][currentRotation][row][col])
            {
                int gridX = currentX + col;
                int gridY = currentY + row;
                if (gridX >= 0 && gridX < 10 && gridY >= 0 && gridY < 20)
                {
                    grid[gridY][gridX] = static_cast<signed char>(currentType);
                }
            }
        }
    }

    // TODO: Check for cleared lines here

    spawnPiece();
}

bool Model::isCollision(int x, int y, int rotation)
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (Tetris::SHAPES[currentType][rotation][row][col])
            {
                int gridX = x + col;
                int gridY = y + row;

                // Wall collision
                if (gridX < 0 || gridX >= 10 || gridY >= 20)
                {
                    return true;
                }

                // Grid collision (landed pieces)
                if (gridY >= 0 && grid[gridY][gridX] != -1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Model::spawnPiece()
{
    currentType = nextType;
    nextType = getRandomPiece();

    // Spawn at top center
    currentX = 3;
    currentY = 0;
    currentRotation = 0;

    // Check if new piece immediately collides (Game Over)
    if (isCollision(currentX, currentY, currentRotation))
    {
        // Reset grid for now
        for (int y = 0; y < 20; y++)
            for (int x = 0; x < 10; x++)
                grid[y][x] = -1;
    }
}

Tetris::TetrominoType Model::getRandomPiece()
{
    return static_cast<Tetris::TetrominoType>(rand() % Tetris::COUNT);
}
