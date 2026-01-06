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
    void hardDrop();
    void holdPiece();

    // Getters for UI
    Tetris::TetrominoType getCurrentPieceType() const { return currentType; }
    Tetris::TetrominoType getNextPieceType() const { return nextType; }
    Tetris::TetrominoType getHeldPieceType() const { return heldType; }
    int getCurrentX() const { return currentX; }
    int getCurrentY() const { return currentY; }
    int getCurrentRotation() const { return currentRotation; }
    int getGhostY() const;
    signed char getGridValue(int x, int y) const { return grid[y][x]; }

    bool getIsGameOver() const { return isGameOver; }
    int getScore() const { return score; }
    int getLevel() const { return level; }
    int getLines() const { return linesCount; }
    bool getIsPaused() const { return isPaused; }
    void togglePause();
    void resetGame();

protected:
    ModelListener* modelListener;

    signed char grid[20][10];
    
    Tetris::TetrominoType currentType;
    int currentX, currentY;
    int currentRotation;

    Tetris::TetrominoType nextType;
    Tetris::TetrominoType heldType;
    bool hasHeld;

    bool isGameOver;
    bool isPaused;
    int score;
    int level;
    int linesCount;
    int goalLines;

    int tickCounter;
    int dropSpeed; // Ticks per drop

    void spawnPiece();
    void lockPiece();
    void checkLines();
    bool isCollision(int x, int y, int rotation) const;
    Tetris::TetrominoType getRandomPiece();
};

#endif // MODEL_HPP
