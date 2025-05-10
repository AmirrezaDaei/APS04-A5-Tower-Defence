#include "tower.hpp"

Tower::Tower(Vector2f position_, int price_, float cool_down_, Texture &texture_, float radius_)
    : position(position_), price(price_), cool_down(cool_down_), texture(texture_), radius(radius_)
{   
    sprite.setTexture(texture_);
    Vector2u tex_size = texture_.getSize();
    sprite.setScale(TOWER_SIZE / tex_size.x, TOWER_SIZE / tex_size.y);
    sprite.setPosition(position);
}

void Tower::draw(RenderWindow &window)
{
    window.draw(sprite);
}

ShopTower::ShopTower(Vector2f position_, string name_, int price_, float size_, float cool_down_, Texture &texture_, float radius_)
    : Tower(position_, price_,cool_down_, texture_, radius_), name(name_), size(size_) {}

void ShopTower::draw(RenderWindow &window)
{
    Vector2u tex_size = texture.getSize();
    sprite.setScale(size / tex_size.x, size / tex_size.y);

    if (avalible == true)
        sprite.setColor(Color::White);
    else
        sprite.setColor(Color(80, 80, 80));
    window.draw(sprite);
}

int ShopTower::getPrice() { return price; }

float ShopTower::getRadius() { return radius; }

float ShopTower::getCoolDownTime() { return cool_down; }

Texture &ShopTower::getTexture() { return texture; }

bool ShopTower::checkBeingHovered(Vector2f mouse_pos)
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    float centerWidth = spriteBounds.width * 0.5f; 
    float centerHeight = spriteBounds.height * 0.5f; 
    float centerX = spriteBounds.left + (spriteBounds.width - centerWidth) / 2;
    float centerY = spriteBounds.top + (spriteBounds.height - centerHeight) / 2;

    sf::FloatRect centerRect(centerX, centerY, centerWidth, centerHeight);

    return centerRect.contains(mouse_pos);
}

void ShopTower::handleBeingHovered(RenderWindow &window)
{
    FloatRect bounds = sprite.getGlobalBounds();
    RectangleShape description(Vector2f(static_cast<float>(SHOP_WIDTH), DESCRIPTION_HEIGHT));
    description.setPosition(window.getSize().x - static_cast<float>(SHOP_WIDTH),
    static_cast<float>(SCORE_BOARD_HEIGHT + bounds.height));
    description.setFillColor(Color(63, 73, 142));
    description.setOutlineThickness(-8);
    description.setOutlineColor(Color(200, 200, 200));

    Text text;
    Font font;
    if (!font.loadFromFile(DESCRIBTION_FONT_FILENAME))
    {
        cerr << "Could not load scoreboard font\n";
    }
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(Color::White);
    Vector2f position = description.getPosition();
    text.setPosition(position);
    std::ostringstream stream_for_radius;
    stream_for_radius << std::fixed << std::setprecision(0) << radius;
    std::ostringstream stream_for_cooldown;
    stream_for_cooldown << std::fixed << std::setprecision(1) << cool_down;

    string shooter_name;
    if (name == "normal_shooter")
        shooter_name = "Fire Shooter";
    else if (name == "ice_shooter")
        shooter_name = "Ice Shooter";
    else if (name == "cannon")
        shooter_name = "   Cannon";

    text.setString("\n\t" + shooter_name + "\n\n COST: " + to_string(price) + "\n\n\n RADIUS: " + stream_for_radius.str() + "\n\n\n COOLDOWN: " + stream_for_cooldown.str() + " S");

    window.draw(description);
    window.draw(text);
}

void ShopTower::setAvaliblity(bool status)
{
    avalible = status;
}