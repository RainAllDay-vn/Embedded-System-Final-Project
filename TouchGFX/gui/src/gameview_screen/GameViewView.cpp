#include <gui/gameview_screen/GameViewView.hpp>
#include <touchgfx/Color.hpp>

GameViewView::GameViewView()
{

}

void GameViewView::setupScreen()
{
    GameViewViewBase::setupScreen();

    // 1. Configure Matrix Container (Centered: 58 to 182px horizontally)
    // Inner Grid size: 10 columns * 12px = 120px wide, 20 rows * 12px = 240px high.
    // Total size with 2px border on all sides: 124x244
    matrixContainer.setPosition(58, 38, 124, 244);
    
    // 2. Matrix Border (Steel Blue #1B2A41, 2px thickness)
    touchgfx::colortype borderColor = touchgfx::Color::getColorFromRGB(0x1B, 0x2A, 0x41);
    
    // Top border
    matrixBorder[0].setPosition(0, 0, 124, 2);
    // Bottom border
    matrixBorder[1].setPosition(0, 242, 124, 2);
    // Left border
    matrixBorder[2].setPosition(0, 0, 2, 244);
    // Right border
    matrixBorder[3].setPosition(122, 0, 2, 244);

    for (int i = 0; i < 4; i++)
    {
        matrixBorder[i].setColor(borderColor);
        matrixContainer.add(matrixBorder[i]);
    }

    // 3. Matrix Background (Oxford Blue #0A1128)
    matrixBackground.setPosition(2, 2, 120, 240);
    matrixBackground.setColor(touchgfx::Color::getColorFromRGB(0x0A, 0x11, 0x28));
    matrixContainer.add(matrixBackground);

    // 4. Checkerboard Pattern (Subtle highlights #0E1733)
    touchgfx::colortype tileColor = touchgfx::Color::getColorFromRGB(0x0E, 0x17, 0x33);
    int tileIndex = 0;
    for (int row = 0; row < MATRIX_ROWS; row++)
    {
        for (int col = 0; col < MATRIX_COLS; col++)
        {
            // Add a tile only for every second cell to create "interleaved" pattern
            if ((row + col) % 2 == 0)
            {
                matrixTiles[tileIndex].setPosition(2 + col * CELL_SIZE, 2 + row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                matrixTiles[tileIndex].setColor(tileColor);
                matrixContainer.add(matrixTiles[tileIndex]);
                tileIndex++;
            }
        }
    }

    // 5. Add Matrix to the Screen
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
