#ifndef GAMEVIEWVIEW_HPP
#define GAMEVIEWVIEW_HPP

#include <gui_generated/gameview_screen/GameViewViewBase.hpp>
#include <gui/gameview_screen/GameViewPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Container.hpp>

class GameViewView : public GameViewViewBase
{
public:
    GameViewView();
    virtual ~GameViewView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
    static const int MATRIX_COLS = 10;
    static const int MATRIX_ROWS = 20;
    static const int CELL_SIZE = 12;

    touchgfx::Container matrixContainer;
    touchgfx::Box matrixBackground;
    touchgfx::Box verticalLines[MATRIX_COLS + 1];
    touchgfx::Box horizontalLines[MATRIX_ROWS + 1];
};

#endif // GAMEVIEWVIEW_HPP
