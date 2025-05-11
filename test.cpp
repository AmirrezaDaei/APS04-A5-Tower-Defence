#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Scaling");

    sf::Texture texture;
    if (!texture.loadFromFile("./assets/sprites/balloon.png"))
        return -1;

    sf::Sprite sprite(texture);
    sprite.setPosition(400, 300);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

    float duration = .25f; // seconds
    float targetScale = 2.0f; // final scale
    float initialScale = 0.1f;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        float elapsed = clock.getElapsedTime().asSeconds();
        float progress = std::min(elapsed / duration, 1.0f);
        float scale = initialScale + progress * (targetScale - initialScale);

        sprite.setScale(scale, scale);

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
