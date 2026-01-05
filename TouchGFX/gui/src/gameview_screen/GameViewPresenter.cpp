#include <gui/gameview_screen/GameViewView.hpp>
#include <gui/gameview_screen/GameViewPresenter.hpp>

GameViewPresenter::GameViewPresenter(GameViewView& v)
    : view(v)
{

}

void GameViewPresenter::activate()
{
    model->resetGame();
}

void GameViewPresenter::deactivate()
{

}

void GameViewPresenter::modelStateChanged()
{
    view.updateBoard();
}
