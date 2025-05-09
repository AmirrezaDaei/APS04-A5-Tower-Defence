#include "../include/shop.hpp"

Shop::Shop(shared_ptr<TextureManager> texture_manager_, RenderWindow& window) : texture_manager(texture_manager_)
{
    ifstream input(TOWERS_FILENAME);
    string line;
    vector<string> words;

    getline(input, line); // reading the first line
    int count = 0;
    while (getline(input, line))
    {
        words.clear();
        istringstream iss(line);
        string word;
        while (getline(iss, word, ','))
            words.push_back(word);
            float size = static_cast<float>(SHOP_WIDTH / TOWER_COUNT);
        Texture& texture = texture_manager->getTexture(SHOOTERS_FILEPATH + words[t_info::NAME] + ".png");
        Vector2f position(static_cast<float>(window.getSize().x - SHOP_WIDTH) + count * size, static_cast<float>(SCORE_BOARD_HEIGHT));

        shared_ptr<ShopTower> new_tower = make_shared<ShopTower>(position, words[t_info::NAME], 
        stoi(words[t_info::PRICE]), stof(words[t_info::RADIUS]), size, stoi(words[t_info::COOLDOWN]), texture);
        
        towers_in_shop.push_back(new_tower);
        count ++;
    }

}

void Shop::drawShop(RenderWindow& window)
{
    for (auto tower : towers_in_shop)
        tower->draw(window);
}