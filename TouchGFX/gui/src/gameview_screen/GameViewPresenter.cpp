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

void GameViewPresenter::getScoreboard(ScoreInfo* buffer)
{
    // 1. Get High Scores (Top 3)
    int highScores[3];
    model->getHighScores(highScores);

    // 2. Get Current Score
    int currentScore = model->getScore();

    // 3. Fill buffer (unsorted first)
    // First 3 slots are high scores
    for(int i=0; i<3; i++)
    {
        buffer[i].score = highScores[i];
        buffer[i].isCurrent = false;
    }
    // 4th slot is current score
    buffer[3].score = currentScore;
    buffer[3].isCurrent = true;

    // 4. Sort Descending (Bubble sort is fine for 4 items)
    for(int i=0; i<4-1; i++)
    {
        for(int j=0; j<4-i-1; j++)
        {
            if (buffer[j].score < buffer[j+1].score)
            {
                ScoreInfo temp = buffer[j];
                buffer[j] = buffer[j+1];
                buffer[j+1] = temp;
            }
        }
    }
}
