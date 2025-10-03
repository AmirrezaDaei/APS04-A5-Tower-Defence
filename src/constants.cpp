#include "constants.hpp"

int generateRandom(int from, int to) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(from, to);
    return dist(gen);
}

void createText(Text &text, Font &font, int size, Color color) {
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
}

void setSprite(Sprite &sprite, Texture &texture, float size, Vector2f position) {
    sprite.setTexture(texture);
    Vector2u tex_size = texture.getSize();
    sprite.setScale(size / tex_size.x, size / tex_size.y);
    sprite.setPosition(position);
}

void setNormalizedOrigin(sf::Sprite &sprite, float normX, float normY) {
    FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.left + bounds.width * normX, bounds.top + bounds.height * normY);
}

void setCircle(CircleShape &circle, float radius, Color color, Vector2f position) {
    circle.setRadius(radius);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(color);
    circle.setPosition(position);
}

void handleRect(RectangleShape& rect,Vector2f size, Color fill_color, float outline_thikness, Color outline_color, Vector2f position) {
    rect.setSize(size);
    rect.setPosition(position);
    rect.setFillColor(fill_color);
    rect.setOutlineThickness(outline_thikness);
    rect.setOutlineColor(outline_color);
}