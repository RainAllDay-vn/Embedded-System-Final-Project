#include <gui/mainview_screen/MainViewView.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/TypedText.hpp>
#include <cstdlib>

MainViewView::MainViewView()
{

}

void MainViewView::setupScreen()
{
    MainViewViewBase::setupScreen();

    // 1. Background (Oxford Blue #0A1128)
    background.setPosition(0, 0, 240, 320);
    background.setColor(touchgfx::Color::getColorFromRGB(0x0A, 0x11, 0x28));
    add(background);

    // 2. Logo (Centered)
    logo.setBitmap(touchgfx::Bitmap(BITMAP_LOGO_TETRIS_ID));
    logo.setXY((240 - logo.getWidth()) / 2, 40);
    add(logo);

    // 3. Menu Buttons
    // NEW GAME Button
    setupButton(newGameBtn, newGameBtnBackground, newGameBtnBorder, newGameLabel, T_NEW_GAME, 40, 160);
    
    // HIGH SCORES Button
    setupButton(highScoresBtn, highScoresBtnBackground, highScoresBtnBorder, highScoresLabel, T_HIGH_SCORES, 40, 220);

    //setup highscores
    int startX = 75;
    int startY = 265;
    int spacing = 18;

    // Thiết lập 3 dòng điểm nhưng để ẨN ban đầu
    highLines1.setXY(startX, startY);
    highLines1.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xD5, 0x00));
    highLines1.setTypedText(touchgfx::TypedText(T_WILDCARD));
    highLines1.setWildcard(highLines1Buffer);
    highLines1.setVisible(false);
    add(highLines1);

    highLines2.setXY(startX, startY + spacing);
    highLines2.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    highLines2.setTypedText(touchgfx::TypedText(T_WILDCARD));
    highLines2.setWildcard(highLines2Buffer);
    highLines2.setVisible(false);
    add(highLines2);

    highLines3.setXY(startX, startY + (spacing * 2));
    highLines3.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    highLines3.setTypedText(touchgfx::TypedText(T_WILDCARD));
    highLines3.setWildcard(highLines3Buffer);
    highLines3.setVisible(false);
    add(highLines3);

    highLines1.invalidate();
    highLines2.invalidate();
    highLines3.invalidate();

    // 4. Decoration: Some random blocks in background
    touchgfx::BitmapId blocks[] = {
        BITMAP_BLOCK_I_ID, BITMAP_BLOCK_J_ID, BITMAP_BLOCK_L_ID,
        BITMAP_BLOCK_O_ID, BITMAP_BLOCK_S_ID, BITMAP_BLOCK_T_ID, BITMAP_BLOCK_Z_ID
    };

    for (int i = 0; i < 10; i++)
    {
        backgroundBlocks[i].setBitmap(touchgfx::Bitmap(blocks[i % 7]));
        int x = rand() % 228;
        int y = rand() % 400 - 100; // Some start off-screen, some on-screen
        backgroundBlocks[i].setXY(x, y);
        backgroundBlocks[i].setAlpha(40); // Subtle
        backgroundBlockSpeeds[i] = 1 + (rand() % 3); // Speed 1, 2, or 3
        // Insert after background but before logo/buttons
        insert(&background, backgroundBlocks[i]);
    }
}

void MainViewView::handleTickEvent()
{
    static const touchgfx::BitmapId blocks[] = {
        BITMAP_BLOCK_I_ID, BITMAP_BLOCK_J_ID, BITMAP_BLOCK_L_ID,
        BITMAP_BLOCK_O_ID, BITMAP_BLOCK_S_ID, BITMAP_BLOCK_T_ID, BITMAP_BLOCK_Z_ID
    };

    for (int i = 0; i < 10; i++)
    {
        backgroundBlocks[i].moveRelative(0, backgroundBlockSpeeds[i]);
        if (backgroundBlocks[i].getY() > 320)
        {
            // Reset to a random negative Y to create a "disappear and spawn new" effect
            backgroundBlocks[i].setY(-(20 + (rand() % 150))); 
            backgroundBlocks[i].setX(rand() % 228);
            backgroundBlocks[i].setBitmap(touchgfx::Bitmap(blocks[rand() % 7]));
            backgroundBlockSpeeds[i] = 1 + (rand() % 3); // Re-randomize speed too
        }
        backgroundBlocks[i].invalidate();
    }
}

void MainViewView::setupButton(touchgfx::Container& btn, touchgfx::Box& bg, touchgfx::Box* borders, touchgfx::TextArea& label, TypedTextId textId, int x, int y)
{
    btn.setPosition(x, y, 160, 40);
    
    bg.setPosition(0, 0, 160, 40);
    bg.setColor(touchgfx::Color::getColorFromRGB(0x0E, 0x17, 0x33));
    btn.add(bg);

    touchgfx::colortype borderColor = touchgfx::Color::getColorFromRGB(0x1B, 0x2A, 0x41);
    borders[0].setPosition(0, 0, 160, 2); // Top
    borders[1].setPosition(0, 38, 160, 2); // Bottom
    borders[2].setPosition(0, 0, 2, 40); // Left
    borders[3].setPosition(158, 0, 2, 40); // Right
    for (int i = 0; i < 4; i++)
    {
        borders[i].setColor(borderColor);
        btn.add(borders[i]);
    }

    label.setTypedText(touchgfx::TypedText(textId));
    label.setXY(0, 10); // Center vertically (40-20)/2
    label.setWidth(160); // Center horizontally
    label.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    btn.add(label);

    add(btn);
}

void MainViewView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        // 1. NEW GAME Button click check
        if (event.getX() >= 40 && event.getX() <= 200 &&
            event.getY() >= 160 && event.getY() <= 200)
        {
            static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoGameViewScreenNoTransition();
        }

        // 2. THÊM LOGIC CHO NÚT HIGH SCORES (x:40-200, y:220-260)
        if (event.getX() >= 40 && event.getX() <= 200 && event.getY() >= 220 && event.getY() <= 260)
        {
           Unicode::snprintf(highLines1Buffer, 20, "1ST: %d", presenter->getHighScore(0));
           Unicode::snprintf(highLines2Buffer, 20, "2ND: %d", presenter->getHighScore(1));
           Unicode::snprintf(highLines3Buffer, 20, "3RD: %d", presenter->getHighScore(2));

           highLines1.setVisible(true);
           highLines2.setVisible(true);
           highLines3.setVisible(true);

           invalidate();
         }
    }

    MainViewViewBase::handleClickEvent(event);
}

void MainViewView::tearDownScreen()
{
    MainViewViewBase::tearDownScreen();
}
