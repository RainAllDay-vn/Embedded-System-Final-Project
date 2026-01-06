#ifndef MAINVIEWVIEW_HPP
#define MAINVIEWVIEW_HPP

#include <gui_generated/mainview_screen/MainViewViewBase.hpp>
#include <gui/mainview_screen/MainViewPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class MainViewView : public MainViewViewBase
{
public:
    MainViewView();
    virtual ~MainViewView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
    virtual void handleTickEvent();

protected:
    touchgfx::Box background;
    touchgfx::Image logo;

    // Menu Buttons
    touchgfx::Container newGameBtn;
    touchgfx::Box newGameBtnBackground;
    touchgfx::Box newGameBtnBorder[4];
    touchgfx::TextArea newGameLabel;

    touchgfx::Container highScoresBtn;
    touchgfx::Box highScoresBtnBackground;
    touchgfx::Box highScoresBtnBorder[4];
    touchgfx::TextArea highScoresLabel;

    // Decoration (optional but nice)
    touchgfx::Image backgroundBlocks[10];
    int backgroundBlockSpeeds[10];

    touchgfx::TextAreaWithOneWildcard highLines1, highLines2, highLines3;
    touchgfx::Unicode::UnicodeChar highLines1Buffer[20], highLines2Buffer[20], highLines3Buffer[20];

    void setupButton(touchgfx::Container& btn, touchgfx::Box& bg, touchgfx::Box* borders, touchgfx::TextArea& label, TypedTextId textId, int x, int y);
};

#endif // MAINVIEWVIEW_HPP
