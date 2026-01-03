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
    
    // 2. Matrix Background (Oxford Blue #0A1128)
    matrixBackground.setPosition(0, 0, 121, 241);
    matrixBackground.setColor(touchgfx::Color::getColorFromRGB(0x0A, 0x11, 0x28));
    matrixContainer.add(matrixBackground);

    // 3. Grid Lines (Steel Blue #1B2A41)
    touchgfx::colortype gridColor = touchgfx::Color::getColorFromRGB(0x1B, 0x2A, 0x41);

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

    // 5. Left Sidebar (0-60px)
    // HOLD
    holdPanel.setBitmap(touchgfx::Bitmap(BITMAP_PANEL_HOLD_ID));
    holdPanel.setXY(6, 40);
    add(holdPanel);

    holdLabel.setTypedText(touchgfx::TypedText(T_HOLD));
    holdLabel.setXY(6, 25);
    holdLabel.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    add(holdLabel);

    // LEVEL
    levelLabel.setTypedText(touchgfx::TypedText(T_LEVEL));
    levelLabel.setXY(6, 120);
    levelLabel.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    add(levelLabel);

    levelValue.setTypedText(touchgfx::TypedText(T_WILDCARD));
    levelValue.setXY(6, 140);
    levelValue.setColor(touchgfx::Color::getColorFromRGB(0x00, 0xFF, 0x41)); // Neon Green
    Unicode::snprintf(levelBuffer, 8, "01");
    levelValue.setWildcard(levelBuffer);
    add(levelValue);

    // LINES
    linesLabel.setTypedText(touchgfx::TypedText(T_LINES));
    linesLabel.setXY(6, 230);
    linesLabel.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    add(linesLabel);

    linesValue.setTypedText(touchgfx::TypedText(T_WILDCARD));
    linesValue.setXY(6, 250);
    linesValue.setColor(touchgfx::Color::getColorFromRGB(0x00, 0xFB, 0xFF)); // Neon Cyan
    Unicode::snprintf(linesBuffer, 8, "000");
    linesValue.setWildcard(linesBuffer);
    add(linesValue);

    // 6. Right Sidebar (180-240px)
    // NEXT
    nextPanel.setBitmap(touchgfx::Bitmap(BITMAP_PANEL_NEXT_ID));
    nextPanel.setXY(186, 40);
    add(nextPanel);

    nextLabel.setTypedText(touchgfx::TypedText(T_NEXT));
    nextLabel.setXY(186, 25);
    nextLabel.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    add(nextLabel);

    // SCORE
    scorePanel.setBitmap(touchgfx::Bitmap(BITMAP_PANEL_SCORE_ID));
    scorePanel.setXY(186, 120);
    add(scorePanel);

    scoreLabel.setTypedText(touchgfx::TypedText(T_SCORE));
    scoreLabel.setXY(186, 105);
    scoreLabel.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    add(scoreLabel);

    scoreValue.setTypedText(touchgfx::TypedText(T_WILDCARD));
    scoreValue.setXY(186, 140);
    scoreValue.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xD5, 0x00)); // Neon Yellow
    Unicode::snprintf(scoreBuffer, 12, "000000");
    scoreValue.setWildcard(scoreBuffer);
    add(scoreValue);

    // GOAL
    goalLabel.setTypedText(touchgfx::TypedText(T_GOAL));
    goalLabel.setXY(186, 230);
    goalLabel.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    add(goalLabel);

    goalValue.setTypedText(touchgfx::TypedText(T_WILDCARD));
    goalValue.setXY(186, 250);
    goalValue.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0x00, 0x3C)); // Neon Red
    Unicode::snprintf(goalBuffer, 8, "010");
    goalValue.setWildcard(goalBuffer);
    add(goalValue);
}

void GameViewView::tearDownScreen()
{
    GameViewViewBase::tearDownScreen();
}
