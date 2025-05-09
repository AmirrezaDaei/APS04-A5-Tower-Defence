#include "../include/scoreboard.hpp"

ScoreBoard::ScoreBoard(RenderWindow &window)
{
    if (!font.loadFromFile(SCORE_BOARD_FONT_FILENAME))
    {
        cerr << "Could not load scoreboard font\n";
    }
    if (!heart_texture.loadFromFile(HEART_FILENAME))
    {
        cerr << "Could not load heart.png\n";
    }
    heart.setTexture(heart_texture);
    Vector2u tex_size = heart_texture.getSize();
    heart.setScale(HEART_SIZE / tex_size.x, HEART_SIZE / tex_size.y);
    heart.setPosition(window.getSize().x - static_cast<float>(SHOP_WIDTH) + 10, static_cast<float>(SCORE_BOARD_HEIGHT) - 1.5 * HEART_SIZE);

    board.setSize(Vector2f(static_cast<float>(SHOP_WIDTH), static_cast<float>(SCORE_BOARD_HEIGHT)));
    board.setPosition(window.getSize().x - static_cast<float>(SHOP_WIDTH), 0);
    board.setFillColor(Color(220, 179, 46));
    board.setOutlineThickness(-5);
    board.setOutlineColor(Color::Black);

    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(Color::Black);
}

void ScoreBoard::draw(RenderWindow &window)
{
    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    text.setPosition(window.getSize().x - static_cast<float>(SHOP_WIDTH) / 2, 50);
    text.setString("Round  " + to_string(player_stats.round) + "\nMoney:   " + to_string(player_stats.money));

    RectangleShape healthBarBackground(Vector2f(HEALTHBAR_LENGTH, HEALTHBAR_WIDTH));
    healthBarBackground.setFillColor(Color(211, 211, 211));
    healthBarBackground.setPosition(window.getSize().x - static_cast<float>(SHOP_WIDTH) + HEART_SIZE + 20, static_cast<float>(SCORE_BOARD_HEIGHT) - 1.3 * HEART_SIZE);
    healthBarBackground.setOutlineThickness(3);
    healthBarBackground.setOutlineColor(Color::Black);

    RectangleShape healthBar(Vector2f((player_stats.health / MAX_HEALTH) * HEALTHBAR_LENGTH, HEALTHBAR_WIDTH));
    healthBar.setFillColor(Color(144, 238, 144)); 
    Vector2f rectPos = healthBarBackground.getPosition(); 
    healthBar.setPosition(rectPos.x, rectPos.y);


    window.draw(board);
    window.draw(text);
    window.draw(heart);
    window.draw(healthBarBackground);
    window.draw(healthBar);
}