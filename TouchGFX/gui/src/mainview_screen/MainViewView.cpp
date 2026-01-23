#include <gui/mainview_screen/MainViewView.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/TypedText.hpp>
#include <cstdlib>

#ifndef SIMULATOR
#include "main.h"

extern "C" {
    extern RNG_HandleTypeDef hrng;
    #include "SoundEngine.h"
}

static int getRandom(int max) {
    uint32_t val = 0;
    if (HAL_RNG_GenerateRandomNumber(&hrng, &val) == HAL_OK) {
        return val % max;
    }
    return 0;
}
#else
static int getRandom(int max) {
    return rand() % max;
}
#endif

MainViewView::MainViewView()
{

}

void MainViewView::setupScreen()
{
    MainViewViewBase::setupScreen();
    SoundEngine_PlayTrack(TRACK_MENU);

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

    // 4. Decoration: Some random blocks in background
    touchgfx::BitmapId blocks[] = {
        BITMAP_BLOCK_I_ID, BITMAP_BLOCK_J_ID, BITMAP_BLOCK_L_ID,
        BITMAP_BLOCK_O_ID, BITMAP_BLOCK_S_ID, BITMAP_BLOCK_T_ID, BITMAP_BLOCK_Z_ID
    };

    for (int i = 0; i < 10; i++)
    {
        backgroundBlocks[i].setBitmap(touchgfx::Bitmap(blocks[i % 7]));
        int x = getRandom(228);
        int y = getRandom(400) - 100; // Some start off-screen, some on-screen
        backgroundBlocks[i].setXY(x, y);
        backgroundBlocks[i].setAlpha(40); // Subtle
        backgroundBlockSpeeds[i] = 1 + getRandom(3); // Speed 1, 2, or 3
        // Insert after background but before logo/buttons
        insert(&background, backgroundBlocks[i]);
    }
    // 5. Setup High Score Modal (Initially hidden)
    highScoreModal.setPosition(40, 60, 160, 200);
    highScoreModal.setVisible(false);

    // Modal Background (Gunmetal #2A3B55)
    modalBackground.setPosition(0, 0, 160, 200);
    modalBackground.setColor(touchgfx::Color::getColorFromRGB(0x2A, 0x3B, 0x55));
    highScoreModal.add(modalBackground);

    // Modal Border (White)
    touchgfx::colortype modalBorderColor = touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF);
    modalBorder[0].setPosition(0, 0, 160, 2); 
    modalBorder[1].setPosition(0, 198, 160, 2);
    modalBorder[2].setPosition(0, 0, 2, 200);
    modalBorder[3].setPosition(158, 0, 2, 200);
    for(int i=0; i<4; i++)
    {
        modalBorder[i].setColor(modalBorderColor);
        highScoreModal.add(modalBorder[i]);
    }

    // Title
    modalTitle.setTypedText(touchgfx::TypedText(T_HIGH_SCORES));
    modalTitle.setXY(0, 15);
    modalTitle.setWidth(160);
    modalTitle.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xD5, 0x00)); // Gold
    highScoreModal.add(modalTitle);

    // Score Lines
    for(int i=0; i<3; i++)
    {
        scoreLines[i].setTypedText(touchgfx::TypedText(T_WILDCARD));
        scoreLines[i].setXY(0, 60 + (i * 30));
        scoreLines[i].setWidth(160);
        scoreLines[i].setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        Unicode::snprintf(scoreBuffers[i], 10, "000000");
        scoreLines[i].setWildcard(scoreBuffers[i]);
        highScoreModal.add(scoreLines[i]);
    }

    // Close Button (at bottom)
    closeBtn.setPosition(40, 160, 80, 30);
    closeBtnRec.setPosition(0, 0, 80, 30);
    closeBtnRec.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0x00, 0x3C)); // Neon Red
    closeBtn.add(closeBtnRec);

    closeBtnLabel.setTypedText(touchgfx::TypedText(T_WILDCARD));
    
    // Note: We don't have T_CLOSE, so we use wildcard. 
    // Wait, reusing T_WILDCARD for "CLOSE" needs a static buffer if we set it continually.
    // Instead, let's just use "MENU" or wait, "CLOSE" is 5 chars.
    // Let's use T_WILDCARD and hardcode a buffer.
    static touchgfx::Unicode::UnicodeChar closeBufferStatic[10];
    Unicode::snprintf(closeBufferStatic, 10, "CLOSE");
    closeBtnLabel.setWildcard(closeBufferStatic);
    closeBtnLabel.setXY(0, 5);
    closeBtnLabel.setWidth(80);
    closeBtnLabel.setColor(touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    closeBtn.add(closeBtnLabel);
    
    highScoreModal.add(closeBtn);

    add(highScoreModal);
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
            backgroundBlocks[i].setY(-(20 + getRandom(150))); 
            backgroundBlocks[i].setX(getRandom(228));
            backgroundBlocks[i].setBitmap(touchgfx::Bitmap(blocks[getRandom(7)]));
            backgroundBlockSpeeds[i] = 1 + getRandom(3); // Re-randomize speed too
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

void MainViewView::showHighScoreModal()
{
    int scores[3];
    presenter->getHighScores(scores);

    for(int i=0; i<3; i++)
    {
        Unicode::snprintf(scoreBuffers[i], 10, "%06d", scores[i]);
        scoreLines[i].invalidate();
    }
    highScoreModal.setVisible(true);
    highScoreModal.invalidate();
}

void MainViewView::hideHighScoreModal()
{
    highScoreModal.setVisible(false);
    highScoreModal.invalidate();
}

void MainViewView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        // Check Modal interactions first if visible
        if (highScoreModal.isVisible())
        {
            // Close Button relative to modal (40, 160, 80, 30) + Modal Position (40, 60)
            // Absolute position: X=80..160, Y=220..250
            if (event.getX() >= 80 && event.getX() <= 160 &&
                event.getY() >= 220 && event.getY() <= 250)
            {
                hideHighScoreModal();
            }
            // Consume click if modal is open
            return; 
        }

        // NEW GAME Button click check
        if (event.getX() >= 40 && event.getX() <= 200 &&
            event.getY() >= 160 && event.getY() <= 200)
        {
            static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoGameViewScreenNoTransition();
        }

        // HIGH SCORES Button click check
        if (event.getX() >= 40 && event.getX() <= 200 &&
            event.getY() >= 220 && event.getY() <= 260)
        {
            showHighScoreModal();
        }
    }

    MainViewViewBase::handleClickEvent(event);
}

void MainViewView::tearDownScreen()
{
    MainViewViewBase::tearDownScreen();
}
