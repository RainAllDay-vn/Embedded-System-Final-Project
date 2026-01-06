#ifndef GAMEVIEWPRESENTER_HPP
#define GAMEVIEWPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GameViewView;

class GameViewView;

struct ScoreInfo
{
    int score;
    bool isCurrent;
};

class GameViewPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GameViewPresenter(GameViewView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~GameViewPresenter() {}

    // Proxy methods to Model
    Tetris::TetrominoType getCurrentPieceType() { return model->getCurrentPieceType(); }
    Tetris::TetrominoType getNextPieceType() { return model->getNextPieceType(); }
    Tetris::TetrominoType getHeldPieceType() { return model->getHeldPieceType(); }
    int getCurrentX() { return model->getCurrentX(); }
    int getCurrentY() { return model->getCurrentY(); }
    int getCurrentRotation() { return model->getCurrentRotation(); }
    int getGhostY() { return model->getGhostY(); }
    signed char getGridValue(int x, int y) { return model->getGridValue(x, y); }
    int getScore() { return model->getScore(); }
    int getLevel() { return model->getLevel(); }
    int getLines() { return model->getLines(); }
    bool getIsGameOver() { return model->getIsGameOver(); }
    bool getIsPaused() { return model->getIsPaused(); }
    void togglePause() { model->togglePause(); }
    void resetGame() { model->resetGame(); }
    
    // High Score scoreboard (mix of high scores + current score)
    void getScoreboard(ScoreInfo* buffer);

    void handleLeft() { model->moveLeft(); }
    void handleRight() { model->moveRight(); }
    void handleRotate() { model->rotate(); }
    void handleDown() { model->step(); }
    void handleHardDrop() { model->hardDrop(); }
    void handleHoldPiece() { model->holdPiece(); }

    virtual void modelStateChanged();

private:
    GameViewPresenter();

    GameViewView& view;
};

#endif // GAMEVIEWPRESENTER_HPP
