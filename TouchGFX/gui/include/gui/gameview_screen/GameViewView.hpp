#ifndef GAMEVIEWVIEW_HPP
#define GAMEVIEWVIEW_HPP

#include <gui_generated/gameview_screen/GameViewViewBase.hpp>
#include <gui/gameview_screen/GameViewPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>

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

    // Left Sidebar
    touchgfx::Image holdPanel;
    touchgfx::TextArea holdLabel;
    
    touchgfx::TextArea levelLabel;
    touchgfx::TextAreaWithOneWildcard levelValue;
    touchgfx::Unicode::UnicodeChar levelBuffer[8];

    touchgfx::TextArea linesLabel;
    touchgfx::TextAreaWithOneWildcard linesValue;
    touchgfx::Unicode::UnicodeChar linesBuffer[8];

    // Right Sidebar
    touchgfx::Image nextPanel;
    touchgfx::TextArea nextLabel;

    touchgfx::Image scorePanel;
    touchgfx::TextArea scoreLabel;
    touchgfx::TextAreaWithOneWildcard scoreValue;
    touchgfx::Unicode::UnicodeChar scoreBuffer[12];

    touchgfx::TextArea goalLabel;
    touchgfx::TextAreaWithOneWildcard goalValue;
    touchgfx::Unicode::UnicodeChar goalBuffer[8];
};

#endif // GAMEVIEWVIEW_HPP
