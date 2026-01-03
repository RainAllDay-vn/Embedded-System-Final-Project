#include <gui/gameview_screen/GameViewView.hpp>
#include <touchgfx/Color.hpp>

GameViewView::GameViewView()
{

}

void GameViewView::setupScreen()
{
    GameViewViewBase::setupScreen();

    // 1. Configure Matrix Container (Centered: 60 to 180px horizontally)
    // Grid size: 10 columns * 12px = 120px wide, 20 rows * 12px = 240px high.
    // Adding 1px for the last lines: 121x241
    matrixContainer.setPosition(60, 40, 121, 241);
    
    // 2. Matrix Background (Dark)
    matrixBackground.setPosition(0, 0, 121, 241);
    matrixBackground.setColor(touchgfx::Color::getColorFromRGB(0x00, 0x00, 0x00));
    matrixContainer.add(matrixBackground);

    // 3. Grid Lines (#1A1A1A)
    touchgfx::colortype gridColor = touchgfx::Color::getColorFromRGB(0x1A, 0x1A, 0x1A);

    // Vertical lines
    for (int i = 0; i <= MATRIX_COLS; i++)
    {
        verticalLines[i].setPosition(i * CELL_SIZE, 0, 1, 241);
        verticalLines[i].setColor(gridColor);
        matrixContainer.add(verticalLines[i]);
    }

    // Horizontal lines
    for (int i = 0; i <= MATRIX_ROWS; i++)
    {
        horizontalLines[i].setPosition(0, i * CELL_SIZE, 121, 1);
        horizontalLines[i].setColor(gridColor);
        matrixContainer.add(horizontalLines[i]);
    }

    // 4. Add Matrix to the Screen
    add(matrixContainer);
}

void GameViewView::tearDownScreen()
{
    GameViewViewBase::tearDownScreen();
}
