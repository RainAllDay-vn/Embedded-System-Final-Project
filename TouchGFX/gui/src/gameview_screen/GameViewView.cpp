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

    // 7. Header (Top 40px)
    logo.setBitmap(touchgfx::Bitmap(BITMAP_LOGO_TETRIS_ID));
    logo.setXY((240 - logo.getWidth()) / 2, 8);
    add(logo);

    // 8. Footer (Bottom 40px: 280-320px)
    touchgfx::colortype btnBorderColor = touchgfx::Color::getColorFromRGB(0x1B, 0x2A, 0x41);
    touchgfx::colortype btnBgColor = touchgfx::Color::getColorFromRGB(0x0E, 0x17, 0x33);

    // PAUSE Button
    pauseBtnContainer.setPosition(25, 288, 80, 24);
    
    pauseBtnBackground.setPosition(0, 0, 80, 24);
    pauseBtnBackground.setColor(btnBgColor);
    pauseBtnContainer.add(pauseBtnBackground);
    
    // Border for Pause
    pauseBtnBorder[0].setPosition(0, 0, 80, 1); // Top
    pauseBtnBorder[1].setPosition(0, 23, 80, 1); // Bottom
    pauseBtnBorder[2].setPosition(0, 0, 1, 24); // Left
    pauseBtnBorder[3].setPosition(79, 0, 1, 24); // Right
    for(int i=0; i<4; i++) {
        pauseBtnBorder[i].setColor(btnBorderColor);
        pauseBtnContainer.add(pauseBtnBorder[i]);
    }

    pauseButton.setTypedText(touchgfx::TypedText(T_PAUSE));
    pauseButton.setXY(0, 4); // Centered vertically in 24px container
    pauseButton.setWidth(80); // Full width for centering
    pauseButton.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    pauseBtnContainer.add(pauseButton);
    add(pauseBtnContainer);

    // MENU Button
    menuBtnContainer.setPosition(135, 288, 80, 24);
    
    menuBtnBackground.setPosition(0, 0, 80, 24);
    menuBtnBackground.setColor(btnBgColor);
    menuBtnContainer.add(menuBtnBackground);

    // Border for Menu
    menuBtnBorder[0].setPosition(0, 0, 80, 1); // Top
    menuBtnBorder[1].setPosition(0, 23, 80, 1); // Bottom
    menuBtnBorder[2].setPosition(0, 0, 1, 24); // Left
    menuBtnBorder[3].setPosition(79, 0, 1, 24); // Right
    for(int i=0; i<4; i++) {
        menuBtnBorder[i].setColor(btnBorderColor);
        menuBtnContainer.add(menuBtnBorder[i]);
    }

    menuButton.setTypedText(touchgfx::TypedText(T_MENU));
    menuButton.setXY(0, 4);
    menuButton.setWidth(80);
    menuButton.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    menuBtnContainer.add(menuButton);
    add(menuBtnContainer);

    // 9. Game Over Label (Hidden initially)
    gameOverLabel.setTypedText(touchgfx::TypedText(T_GAME_OVER));
    gameOverLabel.setXY(0, 140);
    gameOverLabel.setHeight(40);
    gameOverLabel.setWidth(240);
    gameOverLabel.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0x00, 0x00));
    gameOverLabel.setVisible(false);
    add(gameOverLabel);

    // 10. Initialize Block Bitmaps mapping
    blockBitmaps[Tetris::I] = BITMAP_BLOCK_I_ID;
    blockBitmaps[Tetris::J] = BITMAP_BLOCK_J_ID;
    blockBitmaps[Tetris::L] = BITMAP_BLOCK_L_ID;
    blockBitmaps[Tetris::O] = BITMAP_BLOCK_O_ID;
    blockBitmaps[Tetris::S] = BITMAP_BLOCK_S_ID;
    blockBitmaps[Tetris::T] = BITMAP_BLOCK_T_ID;
    blockBitmaps[Tetris::Z] = BITMAP_BLOCK_Z_ID;

    // 10. Setup Block Pool
    // Fixed blocks (the grid)
    for (int y = 0; y < MATRIX_ROWS; y++)
    {
        for (int x = 0; x < MATRIX_COLS; x++)
        {
            fixedBlocks[y][x].setVisible(false);
            fixedBlocks[y][x].setXY(2 + x * CELL_SIZE, 2 + y * CELL_SIZE);
            matrixContainer.add(fixedBlocks[y][x]);
        }
    }

    // Falling piece blocks
    for (int i = 0; i < 4; i++)
    {
        fallingBlocks[i].setVisible(false);
        matrixContainer.add(fallingBlocks[i]);
    }

    // Next piece blocks (Next panel is at 186, 40, size 48x48)
    // We'll place them relative to the panel
    for (int i = 0; i < 4; i++)
    {
        previewBlocks[i].setVisible(false);
        add(previewBlocks[i]); // Adding to screen directly for simple positioning relative to panel
    }

    // Initial draw
    updateBoard();
}

void GameViewView::updateBoard()
{
    // Synchronize landed blocks from Model
    for (int y = 0; y < MATRIX_ROWS; y++)
    {
        for (int x = 0; x < MATRIX_COLS; x++)
        {
            signed char type = presenter->getGridValue(x, y);
            if (type >= 0 && type < Tetris::COUNT)
            {
                fixedBlocks[y][x].setBitmap(touchgfx::Bitmap(blockBitmaps[type]));
                fixedBlocks[y][x].setVisible(true);
            }
            else
            {
                fixedBlocks[y][x].setVisible(false);
            }
            fixedBlocks[y][x].invalidate();
        }
    }

    // Draw Falling Piece
    Tetris::TetrominoType currentType = presenter->getCurrentPieceType();
    if (currentType != Tetris::NONE)
    {
        drawPiece(currentType, 
                  presenter->getCurrentX(), 
                  presenter->getCurrentY(), 
                  presenter->getCurrentRotation(), 
                  fallingBlocks, 2, 2); // Matrix starts at container +2,+2
    }
    else
    {
        for (int i = 0; i < 4; i++) fallingBlocks[i].setVisible(false);
    }

    // Draw Next Piece Preview
    Tetris::TetrominoType nextType = presenter->getNextPieceType();
    if (nextType != Tetris::NONE)
    {
        // Panel at (186, 40), size 48x48. Blocks 12x12.
        // Center a 4x4 matrix (48x48) inside panel.
        drawPiece(nextType, 0, 0, 0, previewBlocks, 186, 40, true);
    }

    // Update Sidebars (Score, Level, Lines, Goal)
    Unicode::snprintf(scoreBuffer, 12, "%06d", presenter->getScore());
    scoreValue.invalidate();

    Unicode::snprintf(levelBuffer, 8, "%02d", presenter->getLevel());
    levelValue.invalidate();

    Unicode::snprintf(linesBuffer, 8, "%03d", presenter->getLines());
    linesValue.invalidate();

    // Goal is next level requirement (Level * 10)
    Unicode::snprintf(goalBuffer, 8, "%03d", presenter->getLevel() * 10);
    goalValue.invalidate();

    // Handle Game Over
    if (presenter->getIsGameOver())
    {
        gameOverLabel.setVisible(true);
        gameOverLabel.invalidate();
    }
    else
    {
        gameOverLabel.setVisible(false);
    }

    invalidate();
}

void GameViewView::drawPiece(Tetris::TetrominoType type, int x, int y, int rotation, touchgfx::Image* blockArray, int offsetX, int offsetY, bool isRelative)
{
    int blockIdx = 0;
    touchgfx::BitmapId bmp = blockBitmaps[type];

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (Tetris::SHAPES[type][rotation][row][col])
            {
                if (blockIdx < 4)
                {
                    blockArray[blockIdx].setBitmap(touchgfx::Bitmap(bmp));
                    blockArray[blockIdx].setXY(offsetX + (x + col) * 12, offsetY + (y + row) * 12);
                    blockArray[blockIdx].setVisible(true);
                    blockArray[blockIdx].invalidate();
                    blockIdx++;
                }
            }
        }
    }
    
    // Hide unused blocks if any (shouldn't happen with 4 blocks)
    for (; blockIdx < 4; blockIdx++)
    {
        blockArray[blockIdx].setVisible(false);
        blockArray[blockIdx].invalidate();
    }
}

void GameViewView::tearDownScreen()
{
    GameViewViewBase::tearDownScreen();
}

void GameViewView::handleKeyEvent(uint8_t key)
{
    // Typical key codes for Simulator:
    // Left: 71, Right: 72, Up: 73, Down: 74
    // A: 97, D: 100, W: 119, S: 115
    
    switch (key)
    {
    case 71: // Arrow Left
    case 'a':
    case 'A':
        presenter->handleLeft();
        break;
    case 72: // Arrow Right
    case 'd':
    case 'D':
        presenter->handleRight();
        break;
    case 73: // Arrow Up (Rotate)
    case 'w':
    case 'W':
        presenter->handleRotate();
        break;
    case 74: // Arrow Down
    case 's':
    case 'S':
        presenter->handleDown();
        break;
    }

    updateBoard();
}
