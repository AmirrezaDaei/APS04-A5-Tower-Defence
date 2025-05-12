#include "tower.hpp"

Tower::Tower(Vector2f position_, int price_, float cool_down_, Texture &texture_, float radius_)
    : position(position_), price(price_), cool_down(cool_down_), texture(texture_), radius(radius_)
{
    sprite.setTexture(texture_);
    Vector2u tex_size = texture_.getSize();
    sprite.setScale(TOWER_SIZE / tex_size.x, TOWER_SIZE / tex_size.y);
    sprite.setPosition(position);
}

GameTower::GameTower(Vector2f position_, int price_, float cool_down_, Texture &texture_, float radius_)
    : Tower(position_, price_, cool_down_, texture_, radius_)
{
    FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.left + bounds.width / 2.f,
                     bounds.top + bounds.height / 2.f);
    sprite.setTexture(texture_);
    Vector2u tex_size = texture_.getSize();
    sprite.setScale(TOWER_SIZE / tex_size.x, TOWER_SIZE / tex_size.y);
    sprite.setPosition(position);
    radius_circle.setRadius(radius);
    radius_circle.setOrigin(radius_circle.getRadius(), radius_circle.getRadius());
    radius_circle.setPosition(position);
}

FireTower::FireTower(Vector2f position_, int price_, float cool_down_, Texture &texture_, float radius_)
    : GameTower(position_, price_, cool_down_, texture_, radius_) {}

IceTower::IceTower(Vector2f position_, int price_, float cool_down_, Texture &texture_, float radius_)
    : GameTower(position_, price_, cool_down_, texture_, radius_) {}

Cannon::Cannon(Vector2f position_, int price_, float cool_down_, Texture &texture_, float radius_)
    : GameTower(position_, price_, cool_down_, texture_, radius_) {}

ShopTower::ShopTower(Vector2f position_, string name_, int price_, float size_, float cool_down_, Texture &texture_, float radius_)
    : Tower(position_, price_, cool_down_, texture_, radius_), name(name_), size(size_)
{
    FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.left, bounds.top);
}

void ShopTower::draw(RenderWindow &window)
{
    Vector2u tex_size = texture.getSize();
    sprite.setScale(size / tex_size.x, size / tex_size.y);

    if (availble == true)
        sprite.setColor(Color::White);
    else
        sprite.setColor(Color(80, 80, 80));
    window.draw(sprite);
}

void GameTower::draw(RenderWindow &window)
{
    radius_circle.setFillColor(Color(173, 216, 230, 128));
    window.draw(radius_circle);
    window.draw(sprite);
}

int ShopTower::getPrice() { return price; }

float ShopTower::getRadius() { return radius; }

float ShopTower::getCoolDownTime() { return cool_down; }

Texture &ShopTower::getTexture() { return texture; }

bool ShopTower::containsMouse(Vector2i mouse_pos)
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    float centerWidth = spriteBounds.width * 0.5f;
    float centerHeight = spriteBounds.height * 0.5f;
    float centerX = spriteBounds.left + (spriteBounds.width - centerWidth) / 2;
    float centerY = spriteBounds.top + (spriteBounds.height - centerHeight) / 2;

    sf::FloatRect centerRect(centerX, centerY, centerWidth, centerHeight);

    return centerRect.contains(mouse_pos.x, mouse_pos.y);
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
    Text title;
    Font font;
    if (!font.loadFromFile(DESCRIBTION_FONT_FILENAME))
    {
        cerr << "Could not load scoreboard font\n";
    }
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(Color::White);
    text.setPosition(description.getPosition());
    title.setFont(font);
    title.setCharacterSize(12);
    title.setFillColor(Color::White);

    std::ostringstream stream_for_radius;
    stream_for_radius << std::fixed << std::setprecision(0) << radius;
    std::ostringstream stream_for_cooldown;
    stream_for_cooldown << std::fixed << std::setprecision(1) << cool_down;

    string shooter_name;
    if (name == NORMAL_SHOOTER)
        shooter_name = NORMAL_SHOOTER_TITLE;
    else if (name == ICE_SHOOTER)
        shooter_name = ICE_SHOOTER_TITLE;
    else if (name == CANNON)
        shooter_name = CANNON_TITLE;

    title.setString("\n\n\n\n" + shooter_name);
    FloatRect textBounds = title.getLocalBounds();
    title.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    title.setPosition(description.getPosition().x + SHOP_WIDTH / 2.f, description.getPosition().y);
    text.setString("\n\n\n COST: " + to_string(price) + "\n\n\n RADIUS: " + stream_for_radius.str() + "\n\n\n COOLDOWN: " + stream_for_cooldown.str() + " S");

    window.draw(description);
    window.draw(title);
    window.draw(text);
}

void ShopTower::setAvailblity(bool status)
{
    availble = status;
}

void ShopTower::highlight(RenderWindow &window)
{
    FloatRect bounds = sprite.getGlobalBounds();

    RectangleShape highlightRect;
    highlightRect.setSize(Vector2f(bounds.width, bounds.height));
    highlightRect.setPosition(bounds.left, bounds.top);
    highlightRect.setFillColor(Color::Transparent);
    highlightRect.setOutlineColor(Color::White);
    highlightRect.setOutlineThickness(-3.f);
    window.draw(highlightRect);
}