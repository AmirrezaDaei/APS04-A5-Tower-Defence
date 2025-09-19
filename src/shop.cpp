#include "../include/shop.hpp"

Shop::Shop(shared_ptr<TextureManager> texture_manager_, RenderWindow &window, int &money_)
    : texture_manager(texture_manager_), hovered_tower(nullptr), money(money_) {
    ifstream input(TOWERS_FILENAME);
    string line, to_be_ignored;
    vector<string> words;

    getline(input, to_be_ignored);
    int count = 0;
    while (getline(input, line)) {
        words.clear();
        istringstream iss(line);
        string word;
        while (getline(iss, word, COMMA_SEPERATOR)) words.push_back(word);

        float size = static_cast<float>(SHOP_WIDTH / TOWER_COUNT);
        Texture &texture = texture_manager->getTexture(SHOOTERS_FILEPATH + words[t_info::NAME] + IMAGE_FORMAT);
        Vector2f position(static_cast<float>(window.getSize().x - SHOP_WIDTH) + count * size, static_cast<float>(SCORE_BOARD_HEIGHT));

        shared_ptr<ShopTower> new_tower = make_shared<ShopTower>(
            position, words[t_info::NAME], stoi(words[t_info::PRICE]), size, stof(words[t_info::COOLDOWN]), texture, stof(words[t_info::RADIUS]));

        towers_in_shop.push_back(new_tower);
        count++;
    }

    shop_rectangle.setSize(Vector2f(SHOP_WIDTH, window.getSize().y - SCORE_BOARD_HEIGHT));
    shop_rectangle.setPosition(window.getSize().x - SHOP_WIDTH, SCORE_BOARD_HEIGHT);
    shop_rectangle.setFillColor(Color(200, 200, 200));
}

void Shop::drawShop(RenderWindow &window) {
    window.draw(shop_rectangle);
    bool avalible;
    for (auto tower : towers_in_shop) {
        if (tower == hovered_tower) tower->handleBeingHovered(window);

        if (tower == tower_to_buy) tower->highlight(window);

        if (tower->getPrice() > money)
            tower->setAvailblity(false);
        else
            tower->setAvailblity(true);

        tower->draw(window);
    }
}

void Shop::handleTowerBeingHovered(Vector2i mouse_pos) {
    for (auto tower : towers_in_shop)
        if (tower->containsMouse(mouse_pos)) {
            hovered_tower = tower;
            return;
        }
    hovered_tower = nullptr;
}

shared_ptr<ShopTower> Shop::handleBuyingTower(Vector2i mouse_pos) {
    for (auto tower : towers_in_shop)
        if (tower->containsMouse(mouse_pos)) {
            if (tower->getPrice() <= money) tower_to_buy = tower;
        }
    return tower_to_buy;
}

void Shop::abortBuying() { tower_to_buy = nullptr; }