#ifndef MODEL_HPP
#define MODEL_HPP

#include <gui/common/TetrisDefinitions.hpp>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    // Movement API
    void moveLeft();
    void moveRight();
    void rotate();
    void step(); // Move down one step (gravity)

    // Getters for UI
    Tetris::TetrominoType getCurrentPieceType() const { return currentType; }
    Tetris::TetrominoType getNextPieceType() const { return nextType; }
    int getCurrentX() const { return currentX; }
    int getCurrentY() const { return currentY; }
    int getCurrentRotation() const { return currentRotation; }
    signed char getGridValue(int x, int y) const { return grid[y][x]; }

protected:
    ModelListener* modelListener;

    signed char grid[20][10];
    
    Tetris::TetrominoType currentType;
    int currentX, currentY;
    int currentRotation;

    Tetris::TetrominoType nextType;

    int tickCounter;
    int dropSpeed; // Ticks per drop

    void spawnPiece();
    void lockPiece();
    bool isCollision(int x, int y, int rotation);
    Tetris::TetrominoType getRandomPiece();
};

#endif // MODEL_HPP
