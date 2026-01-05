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

    virtual void handleKeyEvent(uint8_t key);

    void updateBoard();
protected:
    static const int MATRIX_COLS = 10;
    static const int MATRIX_ROWS = 20;
    static const int CELL_SIZE = 12;

    touchgfx::Container matrixContainer;
    touchgfx::Box matrixBackground;
    touchgfx::Box matrixBorder[4]; // Top, Bottom, Left, Right border
    
    // 100 tiles for checkerboard pattern (every second cell)
    touchgfx::Box matrixTiles[5 * MATRIX_ROWS]; 

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

    touchgfx::TextArea gameOverLabel;

    // Header & Footer
    touchgfx::Image logo;
    touchgfx::TextArea pauseButton;
    touchgfx::TextArea menuButton;
    
    // Button backgrounds and borders
    touchgfx::Container pauseBtnContainer;
    touchgfx::Box pauseBtnBackground;
    touchgfx::Box pauseBtnBorder[4];

    touchgfx::Container menuBtnContainer;
    touchgfx::Box menuBtnBackground;
    touchgfx::Box menuBtnBorder[4];

    // Rendering Pool
    touchgfx::Image fixedBlocks[MATRIX_ROWS][MATRIX_COLS];
    touchgfx::Image fallingBlocks[4];
    touchgfx::Image ghostBlocks[4];
    touchgfx::Image previewBlocks[4];
    
    // Mapping from TetrominoType to Bitmap ID
    touchgfx::BitmapId blockBitmaps[Tetris::COUNT];

    void drawPiece(Tetris::TetrominoType type, int x, int y, int rotation, touchgfx::Image* blockArray, int offsetX, int offsetY, bool isRelative = false);
};

#endif // GAMEVIEWVIEW_HPP
