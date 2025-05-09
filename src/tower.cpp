#include "../include/tower.hpp"

Tower::Tower(Vector2f position_, int price_, float radius_,float cool_down_, Texture& texture_)
: position(position_), price(price_), radius(radius_) ,cool_down(cool_down_), texture(texture_)
{
    sprite.setTexture(texture_);
    Vector2u tex_size = texture_.getSize();
    sprite.setScale(TOWER_SIZE / tex_size.x, TOWER_SIZE / tex_size.y);
    sprite.setPosition(position);
}

void Tower::draw(RenderWindow& window)
{
    window.draw(sprite);
}

ShopTower::ShopTower(Vector2f position_, string name_,int price_, float radius_, float size_, float cool_down_, Texture& texture_)
: Tower(position_,price_, size_, cool_down_, texture_), name(name_), size(size_) {}

void ShopTower::draw(RenderWindow &window)
{
    Vector2u tex_size = texture.getSize();
    sprite.setScale(size / tex_size.x, size / tex_size.y);
    window.draw(sprite);
}

int ShopTower::getPrice() { return price; }

float ShopTower::getRadius() { return radius; }

float ShopTower::getCoolDownTime() { return cool_down; }

Texture& ShopTower::getTexture() {return texture; }

bool ShopTower::checkBeingHovered(Vector2f mouse_pos)
{
    return sprite.getGlobalBounds().contains(mouse_pos);
}

void ShopTower::handleBeingHovered(RenderWindow& window)
{
    FloatRect bounds = sprite.getGlobalBounds();
    RectangleShape highlight(Vector2f(bounds.width, bounds.height));
    highlight.setPosition(bounds.left, bounds.top);
    highlight.setFillColor(Color(255, 255, 255));  

    RectangleShape description(Vector2f(static_cast<float>(SHOP_WIDTH), DESCRIPTION_HEIGHT));
    description.setPosition(window.getSize().x - static_cast<float>(SHOP_WIDTH), 
    static_cast<float>(SCORE_BOARD_HEIGHT + bounds.height));
    description.setFillColor(Color(255, 255, 255)); 

    Text text;
    Font font;
    if (!font.loadFromFile(DESCRIBTION_FONT_FILENAME))
    {
        cerr << "Could not load scoreboard font\n";
    }
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(Color::Black);
    Vector2f position = description.getPosition();
    text.setPosition(position);
    std::ostringstream stream_for_radius;
    stream_for_radius << std::fixed << std::setprecision(0) << radius;  
    std::ostringstream stream_for_cooldown;
    stream_for_cooldown << std::fixed << std::setprecision(1) << cool_down;  
    text.setString(name + "\n\nCOST: " + to_string(price) + "\n\nSHOOTING RADIUS: " + stream_for_radius.str()
    + "\n\nCOOL DOWN TIME: " + stream_for_cooldown.str() + " S");

    window.draw(description);
    window.draw(highlight);
    window.draw(text);



}