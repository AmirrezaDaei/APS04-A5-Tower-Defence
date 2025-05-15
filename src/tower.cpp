#include "tower.hpp"

Tower::Tower(Vector2f position_, int price_, float cooldown_, Texture &texture_, float radius_)
    : position(position_), price(price_), cooldown(cooldown_), texture(texture_), radius(radius_)
{
    sprite.setTexture(texture_);
    Vector2u tex_size = texture_.getSize();
    sprite.setScale(TOWER_SIZE / tex_size.x, TOWER_SIZE / tex_size.y);
    sprite.setPosition(position);
}

GameTower::GameTower(Vector2f position_, int price_, float cooldown_, Texture &texture_, float radius_)
    : Tower(position_, price_, cooldown_, texture_, radius_)
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
    radius_circle.setFillColor(Color(173, 216, 230, 50));
    radius_circle.setPosition(position);
}

FireTower::FireTower(Vector2f position_, int price_, float cooldown_, Texture &texture_, float radius_)
    : GameTower(position_, price_, cooldown_, texture_, radius_) {}

IceTower::IceTower(Vector2f position_, int price_, float cooldown_, Texture &texture_, float radius_)
    : GameTower(position_, price_, cooldown_, texture_, radius_) {}

Cannon::Cannon(Vector2f position_, int price_, float cooldown_, Texture &texture_, float radius_)
    : GameTower(position_, price_, cooldown_, texture_, radius_) 
    {
        radius_circle.setRadius(radius - BOMB_RADIUS);
        radius_circle.setOrigin(radius_circle.getRadius(), radius_circle.getRadius());
    }

ShopTower::ShopTower(Vector2f position_, string name_, int price_, float size_, float cooldown_, Texture &texture_, float radius_)
    : Tower(position_, price_, cooldown_, texture_, radius_), name(name_), size(size_)
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
    window.draw(radius_circle);
    window.draw(sprite);
}

bool Tower::containsMouse(Vector2i mouse_pos)
{
    FloatRect spriteBounds = sprite.getGlobalBounds();
    float centerWidth = spriteBounds.width * 0.75f;
    float centerHeight = spriteBounds.height * 0.75f;
    float centerX = spriteBounds.left + (spriteBounds.width - centerWidth) / 2;
    float centerY = spriteBounds.top + (spriteBounds.height - centerHeight) / 2;

    FloatRect centerRect(centerX, centerY, centerWidth, centerHeight);

    return centerRect.contains(mouse_pos.x, mouse_pos.y);
}

void ShopTower::handleBeingHovered(RenderWindow &window)
{
    FloatRect bounds = sprite.getGlobalBounds();
    RectangleShape description(Vector2f(SHOP_WIDTH, DESCRIPTION_HEIGHT));
    description.setPosition(window.getSize().x - SHOP_WIDTH,
                            SCORE_BOARD_HEIGHT + bounds.height);
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
    std::ostringstream stream_for_cooldown;
    stream_for_radius << std::fixed << std::setprecision(0) << radius;
    stream_for_cooldown << std::fixed << std::setprecision(1) << cooldown;

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

bool GameTower::readyToShoot()
{
    if (locked_in_enemy == nullptr && clock.getElapsedTime().asSeconds() >= cooldown)
    {
        return true;
        clock.restart();
    }
    else
        return false;
}

r_dir normalizeRotation(float angle)
{
    if (angle == 0)
        return ND;
    angle = fmod(angle, 360.0f);
    if (angle < 0)
        angle += 360.0f;

    float cw = 360.0f - angle;
    float ccw = angle;

    return (cw < ccw) ? CW : CCW;
}

void GameTower::rotateTower(float dt)
{
    if (locked_in_enemy != nullptr)
    {
        float alpha1 = sprite.getRotation();
        double x = locked_in_enemy->getPosition().x - position.x;
        double y = position.y - locked_in_enemy->getPosition().y;
        double radians = atan2(x, y);
        float alpha2 = radians * (180.0 / M_PI);
        float rotation = alpha1 - alpha2;
        r_dir direction = normalizeRotation(rotation);
        if (direction == CW)
            sprite.rotate(dt * ROTATION_SPEED);
        else if (direction == CCW)
            sprite.rotate(dt * -ROTATION_SPEED);
    }
}

bool GameTower::isInRange(Vector2f pos)
{
    float distance = getDistance(position, pos);
    return distance < radius;
}

float getDistance(Vector2f pos1, Vector2f pos2)
{
    float distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
    return distance;
}

void FireTower::selectEnemy(vector<shared_ptr<Balloon>> enemies_in_range)
{
    map<float ,shared_ptr<Balloon>> enemy_distance_map;
    for (auto enemy : enemies_in_range)
    {
        if (enemy->isLockedOn() == false)
            enemy_distance_map[getDistance(position, enemy->getPosition())] = enemy;
    }
    if (enemy_distance_map.empty() == false)
    {
        locked_in_enemy = enemy_distance_map.begin()->second;
        locked_in_enemy->setLockedOn();
    }
}

void IceTower::selectEnemy(vector<shared_ptr<Balloon>> enemies_in_range)
{
    map<float ,shared_ptr<Balloon>> enemy_distance_map;
    for (auto enemy : enemies_in_range)
    {
        if (enemy->isFrozen() == false && enemy->isLockedOn() == false)
            enemy_distance_map[getDistance(position, enemy->getPosition())] = enemy;
    }
    if (enemy_distance_map.empty() == false)
    {
        locked_in_enemy = enemy_distance_map.begin()->second;
    }
}

void Cannon::selectEnemy(vector<shared_ptr<Balloon>> enemies_in_range)
{
    map<int, shared_ptr<Balloon>, greater<int>> enemy_casualties_map;
    for (auto enemy : enemies_in_range)
    {
        if (getDistance(position, enemy->getPosition()) < radius && enemy->isLockedOn() == false)
            enemy_casualties_map[getBombCasualties(enemy->getPosition(), enemies_in_range)] = enemy;
    }
    if (enemy_casualties_map.empty() == false)
    {
        locked_in_enemy = enemy_casualties_map.begin()->second;
        locked_in_enemy->setLockedOn();
    }
}

int getBombCasualties(Vector2f bomb_pos, vector<shared_ptr<Balloon>> enemies_in_range)
{
    CircleShape bomb_radius(BOMB_RADIUS);
    bomb_radius.setPosition(bomb_pos);
    int count = 0;
    for (auto enemy : enemies_in_range)
        if (getDistance(bomb_pos, enemy->getPosition()) < BOMB_RADIUS)
            count++;
    return count;
}