#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "cmsis_os.h"

#include <cstdlib>
#include <ctime>

extern osMessageQueueId_t inputQueueHandle;

Model::Model() : 
    modelListener(0)
{
    srand(static_cast<unsigned int>(time(NULL)));
    resetGame();
}

void Model::resetGame()
{
    isGameOver = false;
    isPaused = false;
    score = 0;
    level = 1;
    linesCount = 0;
    goalLines = 10;
    tickCounter = 0;
    dropSpeed = 60;
    currentType = Tetris::NONE;
    nextType = Tetris::NONE;

    // Initialize grid
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            grid[y][x] = -1;
        }
    }

    nextType = getRandomPiece();
    spawnPiece();

    if (modelListener != 0)
    {
        modelListener->modelStateChanged();
    }
}

void Model::tick()
{
    if (isGameOver || isPaused)
    {
        return;
    }

    tickCounter++;
    if (tickCounter >= dropSpeed)
    {
        tickCounter = 0;
        step();
    }
    
    uint8_t key = 0;
    while (osMessageQueueGet(inputQueueHandle, &key, NULL, 0) == osOK)
    {
        switch (key)
        {
            case 'U': rotate(); break; // PB12
            case 'R': moveRight(); break; // PB13
            case 'D': step(); break; // PG2
            case 'L': moveLeft(); break; // PG3
            default: break;
        }
    }

    if (modelListener != 0)
    {
        modelListener->modelStateChanged();
    }
}

void Model::moveLeft()
{
    if (isGameOver || isPaused) return;
    if (!isCollision(currentX - 1, currentY, currentRotation))
    {
        currentX--;
    }
}

void Model::moveRight()
{
    if (isGameOver || isPaused) return;
    if (!isCollision(currentX + 1, currentY, currentRotation))
    {
        currentX++;
    }
}

void Model::rotate()
{
    if (isGameOver || isPaused) return;
    int nextRotation = (currentRotation + 1) % 4;
    if (!isCollision(currentX, currentY, nextRotation))
    {
        currentRotation = nextRotation;
    }
}

void Model::step()
{
    if (isGameOver || isPaused) return;
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

    checkLines();
    spawnPiece();
}

void Model::checkLines()
{
    int clearedInThisStep = 0;

    for (int y = 19; y >= 0; y--)
    {
        bool isFull = true;
        for (int x = 0; x < 10; x++)
        {
            if (grid[y][x] == -1)
            {
                isFull = false;
                break;
            }
        }

        if (isFull)
        {
            clearedInThisStep++;
            // Shift everything above down
            for (int shiftY = y; shiftY > 0; shiftY--)
            {
                for (int x = 0; x < 10; x++)
                {
                    grid[shiftY][x] = grid[shiftY - 1][x];
                }
            }
            // Clear top line
            for (int x = 0; x < 10; x++)
            {
                grid[0][x] = -1;
            }
            // Re-check this same Y index since it now contains the row from above
            y++;
        }
    }

    if (clearedInThisStep > 0)
    {
        linesCount += clearedInThisStep;
        
        // Simple scoring: 100, 300, 500, 800
        int points[] = {0, 100, 300, 500, 800};
        score += points[clearedInThisStep] * level;

        // Level up every 10 lines
        if (linesCount >= goalLines)
        {
            level++;
            goalLines += 10;
            // Increase speed (minimum 5 ticks)
            if (dropSpeed > 10) dropSpeed -= 5;
        }
    }
}

bool Model::isCollision(int x, int y, int rotation) const
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (Tetris::SHAPES[currentType][rotation][row][col])
            {
                int gridX = x + col;
                int gridY = y + row;

                if (gridX < 0 || gridX >= 10 || gridY >= 20) return true;
                if (gridY >= 0 && grid[gridY][gridX] != -1) return true;
            }
        }
    }
    return false;
}

void Model::spawnPiece()
{
    currentType = nextType;
    nextType = getRandomPiece();
    currentX = 3;
    currentY = 0;
    currentRotation = 0;

    if (isCollision(currentX, currentY, currentRotation))
    {
        isGameOver = true;
    }
}

Tetris::TetrominoType Model::getRandomPiece()
{
    return static_cast<Tetris::TetrominoType>(rand() % Tetris::COUNT);
}

int Model::getGhostY() const
{
    int ghostY = currentY;
    while (!isCollision(currentX, ghostY + 1, currentRotation))
    {
        ghostY++;
    }
    return ghostY;
}

void Model::togglePause()
{
    if (isGameOver) return;
    isPaused = !isPaused;
}
