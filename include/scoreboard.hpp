#ifndef SCORE_BOARD_HPP
#define SCORE_BOARD_HPP

#include <SFML/Graphics.hpp>
#include "constants.hpp"
using namespace sf;

class ScoreBoard
{
public:
    ScoreBoard(RenderWindow& window);
    void drawScoreBoard(RenderWindow& window, PlayerStats player_stats);

private:
    Font font;
    Texture heart_texture;
    Sprite heart;
    RectangleShape board;
    Text text;
};

#endif // define SCORE_BOARD_HPP